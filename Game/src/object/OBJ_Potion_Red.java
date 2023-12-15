package object;

import entity.Entity;
import main.GamePanel;

public class OBJ_Potion_Red extends Entity {
	GamePanel gp;
	public static final String objName = "Red Potion";
	
	public OBJ_Potion_Red(GamePanel gp) {
		super(gp);
		
		this.gp = gp;
		
		type = type_consumable;
		value = 5;
		name = objName;
		down1 = setup("/objects/potion_red", gp.tileSize, gp.tileSize);
		description = "[Red Potion]\nRestore " + value + " HP.";
		price = 25;
		stackable = true;
		
		setDialogue();
	}
	
	public void setDialogue() {
		dialogues[0][0] = "You drank " + name + "!\n" + "Restore " + value + " HP.";
	}
	
	public boolean use(Entity entity) {
		startDialogue(this, 0);
		entity.life += value;
		gp.playSE(2);
		
		return true;
	}
}
