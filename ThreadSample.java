class ThreadClass extends Thread { // 'Thread' Class를 상속받는다 
    String thread_name; 
    public ThreadClass(String name) { 
        this.thread_name = name; 
    } 

    public void run() { 
        for(int i=0; i<10; i++) { 
            System.out.println(thread_name+i); 
            try { 
                sleep(10); 
            } catch (InterruptedException e) { e.printStackTrace(); } 
        } 
    } 
} 

public class ThreadSample { 
    public static void main(String[] args) throws InterruptedException { 
        ThreadClass tc1 = new ThreadClass("[Thread1] ");
        ThreadClass tc2 = new ThreadClass("[Thread2] ");
        tc1.start(); 
        tc2.start();

        for (int i=0; i<10; i++)
        {
        	System.out.println("[Main] "+i);
        	Thread.sleep(10);
        }
        
        tc1.join();
        tc2.join();
    } 
}