/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package lab1;
import java.util.Scanner;

/**
 *
 * @author sergiu
 */
public class MagicSquare {
    public static void BuildMatrix(){
        int n;
        Scanner in = new Scanner(System.in);
        n = in.nextInt();
        if (n%2 == 0){
            System.out.println("Bad number input!");
            return;
        }
        
        long[][] square = new long [n][n];
        
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j){
                square[i][j] = n * ((i + j + 1 + n / 2) % n) + (i + 2 * j + 1) % n + 1;
            }
        
        int sum;
        for (int i = 0; i < n; ++i){
            if (SumLine(square, n, i) != 1L*n * (n * n + 1) / 2){
                System.out.println("Line Sum not equal to the magic constant!");
                return;
            }
            
            if (SumCol(square, n, i) != 1L*n * (n * n + 1) / 2){
                System.out.println("Col Sum not equal to the magic constant!");
                return;
            }
            
            if (SumDiagPrinc(square, n, i) != 1L*n * (n * n + 1) / 2){
                System.out.println("DiagPrinc Sum not equal to the magic constant!");
                return;
            }
            
            if (SumDiagSec(square, n, i) != 1L*n * (n * n + 1) / 2){
                System.out.println("DiagSec Sum not equal to the magic constant!");
                return;
            }
        }
        
        if (n <= 10)
            ShowMatrix(square, n, n);
        else
        {
            System.out.println(1L *n * (n * n + 1) / 2);
            
        }
    }
    
    public static void ShowMatrix (long [][]matrix, int lines, int cols){
        for (int i = 0; i < lines; ++i){
            for (int j =0; j < cols; ++j){
                System.out.print(matrix[i][j]);
                System.out.print(" ");
            }
            System.out.println();
        }
    }
    
    public static long SumLine(long [][]matrix, int nrCols, int line){
        long sum = 0;
        
        for (int j = 0; j < nrCols; ++j)
            sum += matrix[line][j];
        
        return sum;
    }
    
    public static long SumCol(long [][]matrix, int nrLines, int col){
        long sum = 0;
        
        for (int i = 0; i < nrLines; ++i)
            sum += matrix[i][col];
        
        return sum;
    }
    
    public static long SumDiagPrinc(long [][]matrix, int n, int diag){
        long sum = 0;
        
        for (int i = 0; i < n; ++i)
            sum += matrix[i][i];
        /*int j = n - 1 - diag;
        
        for (; j < n; ++j)
            sum += matrix[n - 1 - j][j];*/
        
        return sum;
    }
    
    public static long SumDiagSec(long [][]matrix, int n, int diag){
        long sum = 0;
        
        for (int i = 0; i < n; ++i)
            sum += matrix[i][n - i - 1];
        /*int j = diag;
        
        for (; j >= 0; --j)
            sum += matrix[n - 1 - j][j];*/
        
        return sum;
    }
}
