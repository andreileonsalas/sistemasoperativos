import java.net.*;
import java.io.*;
public class DateServer {
  public static void main(String[] args) {
    try {
      ServerSocket sock = new ServerSocket(6017);
      /* now listen for connections */
      while (true) {
        Socket client = sock.accept();
        PrintWriter pout = new
        PrintWriter(client.getOutputStream(), true);
        /* write the quote to the socket */
        pout.println("Las rosas son rojas, las cerezas azules, esta progra es bien lenta");
        /* close the socket and resume */
        /* listening for connections */
        client.close();
      }
    } catch (IOException ioe) {
      System.err.println(ioe);
    }
  }
}

import java.net.*;
import java.io.*;
public class DateClient {
  public static void main(String[] args) {
    try {
      /* make connection to server socket */
      Socket sock = new Socket("127.0.0.1", 6017);
      InputStream in = sock.getInputStream();
      BufferedReader bin = new
      BufferedReader(new InputStreamReader( in ));
      /* read the date from the socket */
      String line;
      while ((line = bin.readLine()) != null)
        System.out.println(line);
      /* close the socket connection*/
      sock.close();
    } catch (IOException ioe) {
      System.err.println(ioe);
    }
  }
}