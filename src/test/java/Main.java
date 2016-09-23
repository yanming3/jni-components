import com.yanming.image.Image;
import com.yanming.image.ImageUtils;

public class Main {

    public static void main(String[] args) {
        String[] paras = new String[]{"convert", "/Users/allan/Downloads/1.jpg", "-thumbnail", "300x300^", "-gravity", "center", "-extent", "300x300", "/Users/allan/Downloads/2.jpg"};
        ImageUtils.process(paras.length, paras);

        Image image = new Image("/Users/allan/Downloads/1.jpg");
        image.crop(50, 50, 50, 50);
        image.writeImage("/Users/allan/Downloads/3.jpg");
        image.close();
    }

}
