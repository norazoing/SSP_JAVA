import java.io.BufferedReader;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;

public class FileServer {

    public static void main(String[] args) throws IOException, InterruptedException {
    	ThreadClass tc = new ThreadClass(); 
        Thread th = new Thread(tc); 
        th.start(); 
    	
	    InputStream in = System.in;
	    InputStreamReader reader = new InputStreamReader(in);
	    BufferedReader br = new BufferedReader(reader);
	    String str;
	    	    
	    while (true)
        {
	    	str = br.readLine();
	    	
			if (str.equals("QUIT"))
			{
				tc.listener.close();
				th.join();
				break;
			}
        }	    
    }

}

class ThreadClass implements Runnable { // Runnable Interface ±¸Çö 
	public ServerSocket listener;   
    public void run() {
    	final int BUF_SIZE = 4096;
    	int recvLen;   	
    	String filename = "test.exe";
    	byte[] buffer = new byte[BUF_SIZE];
    	
        listener = null;
 		try {
			listener = new ServerSocket(27015);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
 		
        try {
            while (true) {
                Socket s = listener.accept();
                InputStream input = s.getInputStream();
                int cnt = 0;
                while ((recvLen = input.read(buffer, 0, BUF_SIZE)) !=  -1) 
                {            	
	               	FileOutputStream fw = new FileOutputStream(".//ServerFiles//"+filename, true);
               		fw.write(buffer, cnt, recvLen);
               		fw.close();
                }
                System.out.println(filename+" is received.");
            }
        } catch (IOException e) {
			// TODO Auto-generated catch block
			//e.printStackTrace();
		}
        finally {
            try {
				listener.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				//e.printStackTrace();
			}
        } 		
    } 
} 