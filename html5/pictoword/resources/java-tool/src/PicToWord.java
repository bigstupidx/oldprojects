public class PicToWord {
  /**
   * @param args
   */
  public static void main(String[] args) {
    // System.out.print("args.length: " + args.length + "\n");
    // for (int i = 0; i < args.length; i++) {
    // System.out.print(i + ": " + args[i]);
    // }

    String file;
    if (args.length == 0) {
      file = "doc.txt";
    } else {
      file = args[0];
    }

    Parser parser = new Parser(file);
    parser.save(file);
  }
}
