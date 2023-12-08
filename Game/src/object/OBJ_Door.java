package object;

import java.io.IOException;

import javax.imageio.ImageIO;

public class OBJ_Door extends SuperObject {
	public OBJ_Door() {
		name = "Door";
		
		try {
			image = ImageIO.read(getClass().getResourceAsStream("/objects/dungeon_cave.png"));
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		collision = true;
	}
}
