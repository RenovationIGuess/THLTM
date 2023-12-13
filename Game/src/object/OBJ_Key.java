package object;

import entity.Entity;
import main.GamePanel;

public class OBJ_Key extends Entity {
	GamePanel gp;
	
	public OBJ_Key(GamePanel gp) {
		super(gp);
		this.gp = gp;
		
		type = type_consumable;
		name = "Key";
		description = "[" + name + "]\nUse to open door.";
		down1 = setup("/objects/key", gp.tileSize, gp.tileSize);
		price = 999;
	}
	
	public boolean use(Entity entity) {
		gp.gameState = gp.dialogueState;
		
		int objIndex = getDetected(entity, gp.obj, "Door");
		
		if (objIndex != 999) {
			gp.ui.currentDialogue = "You used " + name + " to open the door.";
			gp.playSE(3);
			gp.obj[gp.currentMap][objIndex] = null;
			return true;
		}
		else {
			gp.ui.currentDialogue = "What are you doing?";
			return false;
		}
	}
}
