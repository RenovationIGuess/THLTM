package object;

import entity.NPC_OldMan;
import main.GamePanel;
import monster.MON_GreenSlime;
import object.OBJ_Key;

public class AssetSetter {
	GamePanel gp;
	
	public AssetSetter(GamePanel gp) {
		this.gp = gp;
	}
	
	public void setObject() {
		gp.obj[0] = new OBJ_Door(gp);
		gp.obj[0].worldX = gp.tileSize * 21;
		gp.obj[0].worldY = gp.tileSize * 22;
		
		gp.obj[1] = new OBJ_Door(gp);
		gp.obj[1].worldX = gp.tileSize * 23;
		gp.obj[1].worldY = gp.tileSize * 25;
	}
	
	public void setNPC() {
		gp.npc[0] = new NPC_OldMan(gp);
		gp.npc[0].worldX = gp.tileSize * 21;
		gp.npc[0].worldY = gp.tileSize * 21;
		
		gp.npc[1] = new NPC_OldMan(gp);
		gp.npc[1].worldX = gp.tileSize * 11;
		gp.npc[1].worldY = gp.tileSize * 21;
		
		gp.npc[2] = new NPC_OldMan(gp);
		gp.npc[2].worldX = gp.tileSize * 31;
		gp.npc[2].worldY = gp.tileSize * 21;
		
		gp.npc[2] = new NPC_OldMan(gp);
		gp.npc[2].worldX = gp.tileSize * 21;
		gp.npc[2].worldY = gp.tileSize * 11;
		
		gp.npc[2] = new NPC_OldMan(gp);
		gp.npc[2].worldX = gp.tileSize * 21;
		gp.npc[2].worldY = gp.tileSize * 31;
	}
	
	public void setMonster() {
		gp.monster[0] = new MON_GreenSlime(gp);
		gp.monster[0].worldX = gp.tileSize * 23;
		gp.monster[0].worldY = gp.tileSize * 36;
		
		gp.monster[1] = new MON_GreenSlime(gp);
		gp.monster[1].worldX = gp.tileSize * 23;
		gp.monster[1].worldY = gp.tileSize * 37;
	}
}
