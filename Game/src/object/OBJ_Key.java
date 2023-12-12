package object;

import entity.Entity;
import main.GamePanel;

public class OBJ_Key extends Entity {
	public OBJ_Key(GamePanel gp) {
		super(gp);
		
		name = "Key";
		description = "[" + name + "]\nUse to open door.";
		down1 = setup("/objects/key", gp.tileSize, gp.tileSize);
	}
}
