/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package lab1;

import java.util.concurrent.TimeUnit;

/**
 *
 * @author sergiu
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        long startTime, endTime;
        startTime = System.nanoTime();
        // TODO code application logic here
        System.out.println("Hello world");
        String []languages = {"C", "C++", "C#", "Go", "JavaScript", "Perl", "PHP", "Python", "Swift", "Java"};
        int n = (int) (Math.random() * 1000000);
        int nmult = (n * 3 + 0b10101 + 0xFF) * 6;
        int naux;
        while (nmult > 9){
            naux = 0;
            while (nmult != 0){
                naux += nmult%10;
                nmult/=10;
            }
            nmult = naux;
        }
        System.out.println(languages[nmult]);
        MagicSquare.BuildMatrix();
        
        endTime = System.nanoTime();
        
        System.out.println(TimeUnit.NANOSECONDS.toSeconds(endTime - startTime));
    }
}
