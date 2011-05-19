
import java.util.*;
import java.io.*;


/**
 *
 * @author switchcase
 */
public class P1 {

    /**
     * @param args the command line arguments
     */
    static int v;
    static  ArrayList<String> passed;
    static ArrayList<String> failed;

    public static void main(String[] args) throws IOException {
        // TODO code application logic here
        passed=new ArrayList<String>();
        failed=new ArrayList<String>();
        String dir="/home/switchcase/Online Judge Solutions/EOS 11/1/";
        String infile="tempin";
        String ofile="out";
        String t;
        for(int i=0;i<200;i++) {
            Scanner inp=new Scanner(new FileInputStream(dir+infile+i));
            Scanner outp=new Scanner(new FileInputStream(dir+ofile+i));
            t="";
            int tests=0;
            System.out.println("DONE "+i);
            while(inp.hasNextLine()) {
                if(tests==9999)
                    tests=9999;
                tests++;
                t=inp.nextLine()+"\n";
                if(t.equals("0\n"))break;
                t+=inp.nextLine()+"\n";
                t+=inp.nextLine()+"\n";
                String outLine=outp.nextLine();
                //System.out.println("TEST DONE "+tests);
                if(outLine.equals("failed") && failed.size()<100000) {
                    failed.add(t);
                }
                else if(!outLine.equals("failed"))passed.add(t);
            }
            System.out.println("FAILED ="+failed.size()+"\nPassed = "+passed.size());
        }
        System.out.println("FAILED ="+failed.size()+"\nPassed = "+passed.size());
        String testF="in";
        int TotalFiles=30;
        int p=0,f=0;
        int Np=0,Nf=0;
        for(int i=0;i<TotalFiles;i++) {
            Np=Nf=0;
            File FILE=new File(dir+"/TEST/"+testF+""+i);
            if(!FILE.exists())FILE.createNewFile();
            Writer finalTests=new BufferedWriter(new FileWriter(dir+"/TEST/"+testF+""+i));
            int cases=Math.abs((new Random()).nextInt())%10000;
            if(cases<4000) cases+=4000;
            System.out.println("Writing "+cases+" cases to file no. "+i);
            
            while(cases>0) {
                cases--;
                int forp= (new Random()).nextInt()%1000;
                forp=(forp%39==0)?1:0;
                if(forp==0) {
                    Np++;
                    finalTests.write(passed.get(p));
                    finalTests.flush();
                    p++;
                }
                else {
                    Nf++;
                    finalTests.write(failed.get(f));
                    finalTests.flush();
                    f++;
                }
            }
            finalTests.write("0\n");
            finalTests.flush();
            finalTests.close();
            System.out.println("FILE in"+i+" contains "+Np+" passed and "+Nf+" failed cases.");
        }
    }
}

