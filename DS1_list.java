import java.util.*;
import java.io.*;

public class list_sort {
    public static void main(String[] args) throws IOException {
    	ArrayList<Grade> al = new ArrayList<>(); 
    	
        try {
            ////////////////////////////////////////////////////////////////
            BufferedReader in = new BufferedReader(new FileReader("DS_Sample1.txt"));
            String str;

            while ((str = in.readLine()) != null) {
            	String words[] = str.split(" ");
            	Grade g = new Grade(words[0],Integer.parseInt(words[1]),Integer.parseInt(words[2]),Integer.parseInt(words[3]));
            	al.add(g);
            }
            in.close();
            ////////////////////////////////////////////////////////////////
        } catch (IOException e) {
            System.err.println(e); // 에러가 있다면 메시지 출력
            System.exit(1);
        }
        
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        while (true)
        {
        	String strInput = br.readLine();
        	if (strInput.equals("PRINT"))
        	{
        		Collections.sort(al, (g1, g2) -> g1.getName().compareTo(g2.getName()));
        	}
        	else if (strInput.equals("KOREAN"))
        	{
        		Collections.sort(al, (g1, g2) -> (g2.getKorean() - g1.getKorean()));
        	}
        	else if (strInput.equals("ENGLISH"))
        	{
        		Collections.sort(al, (g1, g2) -> (g2.getEnglish() - g1.getEnglish()));
        	}
        	else if (strInput.equals("MATH"))
        	{
        		Collections.sort(al, (g1, g2) -> (g2.getMath() - g1.getMath()));
        	}
        	else if (strInput.equals("QUIT"))
        	{
        		break;
        	}
        	
    		Iterator<Grade> itr = al.iterator(); 
    		while (itr.hasNext()) {
    			Grade val = itr.next();
    			System.out.println(String.format("%s %d %d %d",val.getName(), val.getKorean(), val.getEnglish(), val.getMath()));
    		}        	
        }  
    }
}

class Grade
{
    private String strName;
    private int Korean;
    private int English;
    private int Math; 

    public Grade(String str, int k, int e, int m)
    {
        strName = str;
        Korean = k;
        English = e;
        Math = m;
    }

    public String getName()
    {
        return strName;
    }
    public void setName(String strName)
    {
        this.strName = strName;
    }
    public int getKorean()
    {
        return Korean;
    }
    public void setProjectA(int n)
    {
        Korean = n;
    }
    public int getEnglish()
    {
        return English;
    }
    public void setProjectB(int n)
    {
        English = n;
    }
    public int getMath()
    {
        return Math;
    }
    public void setMath(int n)
    {
        Math = n;
    }
}