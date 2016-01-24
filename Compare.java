import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Comparator;

public class WateringFlowers_340 {

    private static Reader in;
    private static PrintWriter out;
    
    public static void main(String[] args) throws IOException {
        
        in = new Reader();
        out = new PrintWriter (System.out, true);
        
        int n = in.nextInt(),
                x1 = in.nextInt(),
                y1 = in.nextInt(),
                x2 = in.nextInt(),
                y2 = in.nextInt();
       Distance dis[] = new Distance[n];
       int x0, y0;
       long first, second;
       
       for (int i = 0; i < n; i++) {
           x0 = in.nextInt();
           y0 = in.nextInt();
           first = (x0 - x1)*(1L)*(x0 - x1) + (y0 - y1)*(1L)*(y0 - y1);
           second = (x0 - x2)*(1L)*(x0 - x2) + (y0 - y2)*(1L)*(y0 - y2);
           dis[i] = new Distance(first, second);
       }
       //using only one fixed attribute
       Arrays.sort(dis);
       
       //using one attribute(depending on method created)
       // Arrays.sort(dis, Distance.FirstComparator);
       
       //using multiple attributes
       // Arrays.sort(dis, new DistanceComparatorFirstAndSecond());
       
       /* for (int i = 0; i < dis.length; i++) {
            out.println(dis[i].first);
        }*/
       long[] dp = new long[n];
       dp[n-1] = dis[n-1].second;
       for (int i = n-2; i >= 0; i--)
           dp[i] = Math.max(dp[i+1], dis[i].second);
       
       //this line sucked
       long result = Math.min(dis[n-1].first, dp[0]);
       for (int i = 0; i < n-1; i++)
           result = Math.min(result, dis[i].first + dp[i+1]);
       out.println(result);
       
       out.close();
       in.close();
    }
    
    static class Distance implements Comparable<Distance>{
        long first, second;
        public Distance(long f, long s) {
            this.first = f;
            this.second = s;
        }
        //inherited abstract method(must) for Comparable interface
        public int compareTo(Distance d) {
            return Long.compare(this.first, d.first);
        }   
    }
    
    /*   
    static class Distance {
        long first, second;
        public Distance(long f, long s) {
            this.first = f;
            this.second = s;
        }
        
        public static Comparator<Distance> FirstComparator = new Comparator<Distance>() {
            public int compare(Distance d1, Distance d2) {
                return Long.compare(d1.first, d2.first);
            }
        };
        
        public static Comparator<Distance> SecondComparator = new Comparator<Distance>() {
            public int compare(Distance d1, Distance d2) {
                return Long.compare(d1.second, d2.second);
            }
        };
    }
    */
    
    //works irrespective of interface called
    static class DistanceComparatorFirstAndSecond implements Comparator<Distance> {        
        public int compare(Distance d1, Distance d2) {
            int flag = Long.compare(d1.first, d2.first);
            if (flag == 0)
                flag = Long.compare(d1.second, d2.second);
            return flag;
        }
    }

    static class Reader {
        final private int BUFFER_SIZE = 1 << 16;
        private DataInputStream din;
        private byte[] buffer;
        private int bufferPointer, bytesRead;
        public Reader(){
            din=new DataInputStream(System.in);
            buffer=new byte[BUFFER_SIZE];
            bufferPointer=bytesRead=0;
        }

        public Reader(String file_name) throws IOException{
            din=new DataInputStream(new FileInputStream(file_name));
            buffer=new byte[BUFFER_SIZE];
            bufferPointer=bytesRead=0;
        }

        public String readLine() throws IOException{
            byte[] buf=new byte[64]; // line length
            int cnt=0,c;
            while((c=read())!=-1){
                if(c=='\n')break;
                buf[cnt++]=(byte)c;
            }
            return new String(buf,0,cnt);
        }

        public int nextInt() throws IOException{
            int ret=0;byte c=read();
            while(c<=' ')c=read();
            boolean neg=(c=='-');
            if(neg)c=read();
            do{ret=ret*10+c-'0';}while((c=read())>='0'&&c<='9');
            if(neg)return -ret;
            return ret;
        } 

        public long nextLong() throws IOException{
            long ret=0;byte c=read();
            while(c<=' ')c=read();
            boolean neg=(c=='-');
            if(neg)c=read();
            do{ret=ret*10+c-'0';}while((c=read())>='0'&&c<='9');
            if(neg)return -ret;
            return ret;
        }

        public double nextDouble() throws IOException{
            double ret=0,div=1;byte c=read();
            while(c<=' ')c=read();
            boolean neg=(c=='-');
            if(neg)c = read();
            do {ret=ret*10+c-'0';}while((c=read())>='0'&&c<='9');
            if(c=='.')while((c=read())>='0'&&c<='9')
                ret+=(c-'0')/(div*=10);
            if(neg)return -ret;
            return ret;
        }
        
        public char nextChar() throws IOException{
            byte c=read();
            while(c<=' ')c=read();
            return (char)c;
        }
        
        private void fillBuffer() throws IOException{
            bytesRead=din.read(buffer,bufferPointer=0,BUFFER_SIZE);
            if(bytesRead==-1)buffer[0]=-1;
        }
        
        private byte read() throws IOException{
            if(bufferPointer==bytesRead)fillBuffer();
            return buffer[bufferPointer++];
        }
        
        public void close() throws IOException{
            if(din==null) return;
            din.close();
        }
    }
}
