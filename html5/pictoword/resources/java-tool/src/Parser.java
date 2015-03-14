import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Arrays;

public class Parser {
  private String file;
  private final int bufSize = 40 * 1024;
  private char buf[];
  private int offset;
  private int readCount;
  private Data data;

  public Parser() {}

  public Parser(String file) {
    this();

    this.file = file;

    this.buf = new char[bufSize];
    Arrays.fill(this.buf, (char) 0);
    this.offset = 0;
    this.readCount = 0;
    this.data = new Data();

    load();
  }

  public boolean load() {
    boolean ret = false;
    try {
      InputStream is = new FileInputStream(new File(this.file));
      InputStreamReader isr = new InputStreamReader(is, "GBK");
      readCount = isr.read(buf, offset, bufSize - offset);
      while (readCount > 0) {
        parse();
        readCount = isr.read(buf, offset, bufSize - offset);
      }
      isr.close();
      ret = true;
    } catch (FileNotFoundException e) {
      e.printStackTrace();
    } catch (IOException e) {
      e.printStackTrace();
    }
    return ret;
  }

  public void save(String file) {
    String outFileName = file.substring(0, file.lastIndexOf(".")) + ".js";
    System.out.print(outFileName);
    try {
      FileOutputStream out = new FileOutputStream(new File(outFileName));
      // write variable
      out.write(("var database = {" + "\r\n").getBytes());
      // write binaries first
      out.write(("    binaries: [" + "\r\n").getBytes());
      for (Data.Binary binary : this.data.binaries) {
        String temp = "        {" + "\r\n";
        temp += "            index: " + binary.index + ", " + "\r\n";
        temp += "            question: \"" + binary.question + "\", " + "\r\n";
        temp += "            answer: \"" + String.valueOf(binary.answer) + "\"" + "\r\n";
        if (this.data.binaries.size() - 1 == this.data.binaries.indexOf(binary)) {
          temp += "        }" + "\r\n";
        } else {
          temp += "        }," + "\r\n";
        }
        out.write(temp.getBytes());
      }
      out.write("    ],\r\n".getBytes());
      // write multipies
      out.write(("    multiples: [" + "\r\n").getBytes());
      for (Data.Multiple multiple : this.data.multiples) {
        String temp = "        {" + "\r\n";
        temp += "            index: " + multiple.index + ", " + "\r\n";
        temp += "            question: \"" + multiple.question + "\", " + "\r\n";
        temp += "            options: \"" + multiple.options + "\", " + "\r\n";
        temp += "            answer: \"" + multiple.answer + "\"" + "\r\n";
        if (this.data.multiples.size() - 1 == this.data.multiples.indexOf(multiple)) {
          temp += "        }" + "\r\n";
        } else {
          temp += "        }," + "\r\n";
        }
        out.write(temp.getBytes());
      }
      out.write("    ]\r\n".getBytes());
      // tail
      out.write("};\r\n".getBytes());
      out.close();
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

  private void parse() {
    String str = new String(buf);
    String lines[] = str.split("\n");
    int index = 0;

    while (index < lines.length) {
      int questionIndex = 0;

      // is a question?
      int dot = lines[index].indexOf(".");
      if (dot >= 0) {
        String indexStr = lines[index].substring(0, dot);
        try {
          questionIndex = Integer.parseInt(indexStr);
        } catch (NumberFormatException e) {
          e.printStackTrace();
        }
      } else {
        // parse error, no "." in string, go next line.
        System.out.print("parse error, no '.' in question.\n");
        index++;
        continue;
      }

      if (questionIndex == 34) {
        questionIndex = 34;
      }
      // get the answer between curves.
      String answerStr = "";
      int leftCurve = -1;
      int rightCurve = -1;
      int left;
      int right;
      do {
        left = lines[index].substring(leftCurve + 1, lines[index].length()).indexOf("（");
        if (left == -1) {
          left = lines[index].substring(leftCurve + 1, lines[index].length()).indexOf("(");
        }
        leftCurve = left + (leftCurve + 1);

        right = lines[index].substring(rightCurve + 1, lines[index].length()).indexOf("）");
        if (right == -1) {
          right = lines[index].substring(rightCurve + 1, lines[index].length()).indexOf(")");
        }
        rightCurve = right + (rightCurve + 1);

        if (left != -1 && right != -1) {
          String strInCurve = lines[index].substring(leftCurve + 1, rightCurve).trim();
          // is the string in curves the answer?
          if (strInCurve.matches("[a-fx-yA-ZX-Y]*")) {
            // remove repeat answer
            if (!answerStr.contains(strInCurve)) {
              answerStr += strInCurve;
            }
          }
        }
      } while (left != -1 && right != -1);

      if (answerStr.isEmpty()) {
        // parse error, no curves, go next line.
        System.out.print("parse error, no curves in question[" + questionIndex + "].");
        index++;
        continue;
      }

      // is a binary choice question?
      // XY
      if (answerStr.equalsIgnoreCase("X") || answerStr.equalsIgnoreCase("Y")) {
        String question = lines[index].substring(rightCurve + 1, lines[index].length()).trim();
        boolean answer = answerStr.equalsIgnoreCase("Y");

        // add to data.
        this.data.addBinary(questionIndex, question, answer);

        // next question.
        index++;
        continue;
      }

      // is a multiple choice question?
      // ABCDEF
      boolean isMultiple = true;
      for (int i = 0; i < answerStr.length(); i++) {
        char c = answerStr.charAt(i);
        if (!((c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))) {
          isMultiple = false;
        }
      }
      if (isMultiple) {
        String question = lines[index].substring(dot + 1, lines[index].length()).trim();
        String answer = answerStr;
        String options = "";

        int answerPos[] = new int[7];
        Arrays.fill(answerPos, -1);

        int lineAnswerPos[] = new int[7];
        boolean lineHasAnswer;

        do {
          lineHasAnswer = false;
          Arrays.fill(lineAnswerPos, -1);

          // next line
          index++;

          // get position of options
          // A、B、C、D、E、F、
          for (char option = 'A'; option <= 'F'; option++) {
            int pos = lines[index].indexOf(option + "、");
            if (pos >= 0 && answerPos[option - 'A'] == -1) {
              lineHasAnswer = true;
              answerPos[option - 'A'] = pos;
              lineAnswerPos[option - 'A'] = pos;
            }
          }

          // get options string
          for (int i = 0; i < 6; i++) {
            if (lineAnswerPos[i] >= 0) {
              String option;
              if (lineAnswerPos[i + 1] >= 0) {
                option = lines[index].substring(lineAnswerPos[i] + 2, lineAnswerPos[i + 1]).trim();
              } else {
                option = lines[index].substring(lineAnswerPos[i] + 2, lines[index].length()).trim();
              }
              if (i > 0) {
                options += "\t";
              }
              options += option;
            }
          }
        } while (lineHasAnswer && index < lines.length);

        // add to data
        if (!options.isEmpty()) {
          // remove the answer in curves.
          System.out.print("before replace: " + question + "\n");
          String trimQuestion = question;
          do {
            left = trimQuestion.indexOf("(");
            if (left == -1) {
              left = trimQuestion.indexOf("（");
            }

            right = trimQuestion.indexOf(")");
            if (right == -1) {
              right = trimQuestion.indexOf("）");
            }

            if (left != -1 && right != -1) {
              // check if the answer
              String strInCurves = question.substring(left + 1, right).trim();
              boolean isAnswer = true;
              for (int i = 0; i < strInCurves.length(); i++) {
                char c = strInCurves.charAt(i);
                if (!((c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))) {
                  isAnswer = false;
                }
              }
              // replace to "____"
              if (isAnswer) {
                question =
                    question.substring(0, left) + "____"
                        + question.substring(right + 1, question.length());
                trimQuestion =
                    trimQuestion.substring(0, left) + "____"
                        + trimQuestion.substring(right + 1, trimQuestion.length());
              } else {
                // remove cruves in trim question.
                String temp = "";
                for (int i = left; i <= right; i++) {
                  temp += "_";
                }
                trimQuestion =
                    trimQuestion.substring(0, left) + temp
                        + trimQuestion.substring(right + 1, trimQuestion.length());
              }
            }
          } while (left != -1 && right != -1);
          System.out.print("after replace: " + question + "\n");

          // add to data.
          this.data.addMultiple(questionIndex, question, options, answer);
        }

        continue;
      }

      break;
    }
  }
}
