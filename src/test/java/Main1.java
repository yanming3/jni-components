import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Created by allan on 16/9/23.
 */
public class Main1 {
    public static void main(String[] args) throws Exception {
        String ROOT = "/Users/allan/Downloads/";

        List<String> paras1 = Arrays.asList(new String[]{"gm", "convert", "/Users/allan/Downloads/1.jpg", "-thumbnail", "300x300^", "-gravity", "center", "-extent", "300x300"});
        List<String> paras = new ArrayList<String>(paras1);
        long a = System.currentTimeMillis();
        for (int i = 0; i < 10; i++) {
            paras.add(ROOT + i + ".jpg");
            ProcessBuilder builder = new ProcessBuilder(paras);
            Process process=builder.start();
            paras.remove(paras.size() - 1);
        }
        long b = System.currentTimeMillis();
        System.out.println(b - a);
    }
}
