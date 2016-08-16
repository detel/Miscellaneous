/*
* This code is used to increase the recursion stack size of Java.
*/
public class IncreaseStackSize {

    public static void main(String args[]) {
        new Thread(null, new Runnable() {
            public void run() {
                try{
                    solve();
                }
                catch(Exception e){
                    e.printStackTrace();
                }
            }
        }, "1", 1 << 26).start();
    }
    
    public static void solve() {
      // write code here
    }
    
}
