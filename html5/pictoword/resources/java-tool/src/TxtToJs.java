import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

public class TxtToJs {
  /**
   * @param args
   */
  public static void main(String[] args) {
    String file;
    if (args.length == 0) {
      //file = "preload_sheet.plist";
      file = "prompt.txt";
    } else {
      file = args[0];
    }

    TxtToJs.convert(file);
  }

  private static void convert(String file) {
    try {
      // read
      InputStream is = new FileInputStream(new File(file));
      InputStreamReader isr = new InputStreamReader(is, "GBK");
      int readCount;
      int offset = 0;
      int bufSize = 40 * 2048;
      char buf[] = new char[bufSize];
      readCount = isr.read(buf, offset, bufSize - offset);
      isr.close();
      
      // write
      String outFileName = file.substring(0, file.lastIndexOf(".")) + ".js";
      System.out.print(outFileName);
      try {
        FileOutputStream out = new FileOutputStream(new File(outFileName));
        out.write("\"".getBytes());
        for (int i = 0; i < readCount; i++) {
          String t = String.valueOf(buf[i]);
          if (t.equals("\n")) {
            t = "\\n";
          } else if (t.equals("\r")) {
            t = "";
          } else if (t.equals("\t")) {
        	t = "    ";
          } else if (t.equals("\"")) {
        	t = "\\\"";
          }
          out.write(t.getBytes());
        }
        out.write("\"".getBytes());
        out.close();
      } catch (Exception e) {
        e.printStackTrace();
      }
    } catch (FileNotFoundException e) {
      e.printStackTrace();
    } catch (IOException e) {
      e.printStackTrace();
    }
  }
}
