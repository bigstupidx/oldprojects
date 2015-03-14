import java.util.ArrayList;

public class Data {
  private final boolean trace = true;

  public enum Type {
    BinaryChoice, SingleMultipleChoice, MultipleChoice
  };

  public class Question {
    int index;
    String question;

    public Question(int index, String question) {
      this.index = index;
      this.question = question;
    }
  };

  public class Binary extends Question {
    boolean answer;

    public Binary(int index, String question, boolean answer) {
      super(index, question);

      this.answer = answer;
    }
  };

  public class Single extends Question {
    String options;
    char answer;

    public Single(int index, String question, String options, char answer) {
      super(index, question);

      this.options = options;
      this.answer = answer;
    }
  };

  public class Multiple extends Question {
    String options;
    String answer;

    public Multiple(int index, String question, String options, String answer) {
      super(index, question);

      this.options = options;
      this.answer = answer;
    }
  };

  public ArrayList<Binary> binaries;
  public ArrayList<Single> singles;
  public ArrayList<Multiple> multiples;

  public Data() {
    this.binaries = new ArrayList<Binary>();
    this.singles = new ArrayList<Single>();
    this.multiples = new ArrayList<Multiple>();
  }

  public void addBinary(int index, String question, boolean answer) {
    Binary binary = new Binary(index, question, answer);
    binaries.add(binary);
    if (trace) {
      System.out.print("add binary[" + index + "]: \n");
      System.out.print(question + "\n");
      System.out.print(answer + "\n");
    }
  }

  public void addSingle(int index, String question, String options, char answer) {
    Single single = new Single(index, question, options, answer);
    singles.add(single);
  }

  public void addMultiple(int index, String question, String options, String answer) {
    Multiple multiple = new Multiple(index, question, options, answer);
    multiples.add(multiple);
    if (trace) {
      System.out.print("add multiple[" + index + "]: \n");
      System.out.print(question + "\n");
      String optionsList[] = options.split("\t");
      char temp = 'A';
      for (String option : optionsList) {
        System.out.print(temp + ": " + option + "\n");
        temp++;
      }
      System.out.print(answer + "\n");
    }
  }

  public void clear() {
    this.binaries.clear();
    this.singles.clear();
    this.multiples.clear();
  }
}
