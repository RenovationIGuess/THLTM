package object;

import entity.Entity;
import main.GamePanel;

public class OBJ_BlueHeart extends Entity {
	GamePanel gp;
	public static final String objName = "Blue Heart";
	
	public OBJ_BlueHeart(GamePanel gp) {
		super(gp);
		this.gp = gp;
		
		type = type_pickUpOnly;
		name = objName;
		down1 = setup("/objects/blueheart", gp.tileSize, gp.tileSize);
		
		setDialogue();
	}
	
	public void setDialogue() {
		dialogues[0][0] = "What a beautiful gem *o*.";
		dialogues[0][1] = "You obtained the Blue Heart, the legendary treasure!";
	}
	
	public boolean use(Entity entity) {
		gp.gameState = gp.cutsceneState;
		gp.csManager.sceneNum = gp.csManager.ending;
		return true;
	}
}
