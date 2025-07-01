import java.io.*;
import java.util.*;

public class Main {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out);
    static StringTokenizer st;

    // Fast Integer
static int nextInt() throws IOException {
    return Integer.parseInt(next());
}

// Fast Long
static long nextLong() throws IOException {
    return Long.parseLong(next());
}

// Fast Double
static double nextDouble() throws IOException {
    return Double.parseDouble(next());
}

// Fast Float
static float nextFloat() throws IOException {
    return Float.parseFloat(next());
}

// Fast Character
static char nextChar() throws IOException {
    return next().charAt(0);  // Gets the first character of next token
}

// Fast Line
static String nextLine() throws IOException {
    return br.readLine();
}

// Fast String (default tokenizer next token)
static String next() throws IOException {
    while (st == null || !st.hasMoreTokens()) {
        st = new StringTokenizer(br.readLine());
    }
    return st.nextToken();
}

// Fast Integer Array
static int[] readIntArray(int n) throws IOException {
    int[] arr = new int[n];
    for (int i = 0; i < n; i++) arr[i] = nextInt();
    return arr;
}

// Fast Long Array
static long[] readLongArray(int n) throws IOException {
    long[] arr = new long[n];
    for (int i = 0; i < n; i++) arr[i] = nextLong();
    return arr;
}



    public static void main(String[] args) throws IOException {
        int t = nextInt();
        while (t-- > 0) solve();
        out.close();
    }

    static void solve() throws IOException {
        // Your logic here
    }

   
}
