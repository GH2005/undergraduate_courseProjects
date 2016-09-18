package AnoPackage;

/**
 * Created with IntelliJ IDEA.
 * User: GH2005
 * Date: 12-12-23
 * Time: 21:26
 * To change this template use File | Settings | File Templates.
 */

 abstract class AbVector {
      int array[];
      protected AbVector(int inArray[])
      {
            array = inArray.clone();
      }
}

public class Vector extends AbVector {
      public Vector(int inArray[])
      {
            super(inArray);
      }
      public void OddEvenExchangeSort()
      {
            int block = 0;
            boolean ok[] = new boolean[]{false, false};
            int okokCount = 0;
            while (okokCount < 2)
            {     // either is false, go on.
                  ok[0] = true;
                  ok[1] = true;
                  for (int i = 0 + block; i < this.array.length - 1; i += 2)
                  {
                        if (array[i] > array[i + 1])
                        {
                              ok[block] = false;
                              int temp = array[i];
                              array[i] = array[i + 1];
                              array[i + 1] = temp;
                        }
                  }
                  if (block == 0)
                  {
                        block = 1;
                  }
                  else if (block == 1)
                  {
                        block = 0;
                  }
                  if (ok[0] & ok[1])
                  {
                        okokCount ++;
                  }
            }
      }
      public void PrintVector()
      {
            System.out.print("Print the vector:");
            for (int i = 0; i < this.array.length; i ++)
            {
                  System.out.print(" " + this.array[i]);
            }
            System.out.println('.');
      }
}


