// experiment task 5.3.
// ****** Java exam approaching, ****** so I use Java to implement it this time, C or C++ requirements ignored.

package ThePackage;
import AnoPackage.*;

public class exTask5_3 implements Runnable{
      public static void main(String[] args)
      {
            Thread t = new Thread(new exTask5_3());
            t.start();
      }
      public void run()
      {
            Vector vec = new Vector(new int[]{2, 5, 3, 8, 10, 19, 16, 33});
            vec.OddEvenExchangeSort();
            vec.PrintVector();
      }
}
