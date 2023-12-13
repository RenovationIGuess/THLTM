package object;

import entity.NPC_Merchant;
import entity.NPC_OldMan;
import main.GamePanel;
import monster.MON_GreenSlime;
import object.OBJ_Key;
import tile_interactive.IT_DryTree;

public class AssetSetter {
	GamePanel gp;
	
	public AssetSetter(GamePanel gp) {
		this.gp = gp;
	}
	
	public void setObject() {
		int mapNum = 0;
		int i = 0;
		
		gp.obj[mapNum][i] = new OBJ_Key(gp);
		gp.obj[mapNum][i].worldX = gp.tileSize * 25;
		gp.obj[mapNum][i].worldY = gp.tileSize * 23;
		
		i++;
		gp.obj[mapNum][i] = new OBJ_Door(gp);
		gp.obj[mapNum][i].worldX = gp.tileSize * 14;
		gp.obj[mapNum][i].worldY = gp.tileSize * 28;
		
		i++;
		gp.obj[mapNum][i] = new OBJ_Door(gp);
		gp.obj[mapNum][i].worldX = gp.tileSize * 12;
		gp.obj[mapNum][i].worldY = gp.tileSize * 12;
		
		i++;
		gp.obj[mapNum][i] = new OBJ_Key(gp);
		gp.obj[mapNum][i].worldX = gp.tileSize * 21;
		gp.obj[mapNum][i].worldY = gp.tileSize * 19;
		
		i++;
		gp.obj[mapNum][i] = new OBJ_Key(gp);
		gp.obj[mapNum][i].worldX = gp.tileSize * 21;
		gp.obj[mapNum][i].worldY = gp.tileSize * 19;
		
		i++;
		gp.obj[mapNum][i] = new OBJ_Key(gp);
		gp.obj[mapNum][i].worldX = gp.tileSize * 26;
		gp.obj[mapNum][i].worldY = gp.tileSize * 21;
		
		i++;
		gp.obj[mapNum][i] = new OBJ_Coin_Bronze(gp);
		gp.obj[mapNum][i].worldX = gp.tileSize * 27;
		gp.obj[mapNum][i].worldY = gp.tileSize * 21;
		
		i++;
		gp.obj[mapNum][i] = new OBJ_Coin_Bronze(gp);
		gp.obj[mapNum][i].worldX = gp.tileSize * 28;
		gp.obj[mapNum][i].worldY = gp.tileSize * 21;
		
		i++;
		gp.obj[mapNum][i] = new OBJ_Coin_Bronze(gp);
		gp.obj[mapNum][i].worldX = gp.tileSize * 29;
		gp.obj[mapNum][i].worldY = gp.tileSize * 21;
		
		i++;
		gp.obj[mapNum][i] = new OBJ_Axe(gp);
		gp.obj[mapNum][i].worldX = gp.tileSize * 33;
		gp.obj[mapNum][i].worldY = gp.tileSize * 21;
		
		i++;
		gp.obj[mapNum][i] = new OBJ_Shield_Blue(gp);
		gp.obj[mapNum][i].worldX = gp.tileSize * 35;
		gp.obj[mapNum][i].worldY = gp.tileSize * 21;
		
		i++;
		gp.obj[mapNum][i] = new OBJ_Chest(gp, new OBJ_Key(gp));
		gp.obj[mapNum][i].worldX = gp.tileSize * 37;
		gp.obj[mapNum][i].worldY = gp.tileSize * 21;
		
		i++;
		gp.obj[mapNum][i] = new OBJ_Potion_Red(gp);
		gp.obj[mapNum][i].worldX = gp.tileSize * 22;
		gp.obj[mapNum][i].worldY = gp.tileSize * 27;
		
		i++;
		gp.obj[mapNum][i] = new OBJ_Heart(gp);
		gp.obj[mapNum][i].worldX = gp.tileSize * 22;
		gp.obj[mapNum][i].worldY = gp.tileSize * 29;
		
		i++;
		gp.obj[mapNum][i] = new OBJ_ManaCrystal(gp);
		gp.obj[mapNum][i].worldX = gp.tileSize * 22;
		gp.obj[mapNum][i].worldY = gp.tileSize * 31;
	}
	
	public void setNPC() {
		int mapNum = 0;
		int i = 0;
		
		gp.npc[mapNum][i] = new NPC_OldMan(gp);
		gp.npc[mapNum][i].worldX = gp.tileSize * 21;
		gp.npc[mapNum][i].worldY = gp.tileSize * 21;
		
//		i++;
//		gp.npc[mapNum][i] = new NPC_OldMan(gp);
//		gp.npc[mapNum][i].worldX = gp.tileSize * 11;
//		gp.npc[mapNum][i].worldY = gp.tileSize * 21;
//		
//		i++;
//		gp.npc[mapNum][i] = new NPC_OldMan(gp);
//		gp.npc[mapNum][i].worldX = gp.tileSize * 31;
//		gp.npc[mapNum][i].worldY = gp.tileSize * 21;
//		
//		i++;
//		gp.npc[mapNum][i] = new NPC_OldMan(gp);
//		gp.npc[mapNum][i].worldX = gp.tileSize * 21;
//		gp.npc[mapNum][i].worldY = gp.tileSize * 11;
//		
//		i++;
//		gp.npc[mapNum][i] = new NPC_OldMan(gp);
//		gp.npc[mapNum][i].worldX = gp.tileSize * 21;
//		gp.npc[mapNum][i].worldY = gp.tileSize * 31;
		
		mapNum = 1;
		i = 0;
		gp.npc[mapNum][i] = new NPC_Merchant(gp);
		gp.npc[mapNum][i].worldX = gp.tileSize * 12;
		gp.npc[mapNum][i].worldY = gp.tileSize * 7;
	}
	
	public void setMonster() {
		int mapNum = 0;
		int i = 0;
		
		gp.monster[mapNum][i] = new MON_GreenSlime(gp);
		gp.monster[mapNum][i].worldX = gp.tileSize * 23;
		gp.monster[mapNum][i].worldY = gp.tileSize * 36;
		
		i++;
		gp.monster[mapNum][i] = new MON_GreenSlime(gp);
		gp.monster[mapNum][i].worldX = gp.tileSize * 23;
		gp.monster[mapNum][i].worldY = gp.tileSize * 37;
		
		i++;
		gp.monster[mapNum][i] = new MON_GreenSlime(gp);
		gp.monster[mapNum][i].worldX = gp.tileSize * 24;
		gp.monster[mapNum][i].worldY = gp.tileSize * 37;
		
		i++;
		gp.monster[mapNum][i] = new MON_GreenSlime(gp);
		gp.monster[mapNum][i].worldX = gp.tileSize * 34;
		gp.monster[mapNum][i].worldY = gp.tileSize * 42;
		
		i++;
		gp.monster[mapNum][i] = new MON_GreenSlime(gp);
		gp.monster[mapNum][i].worldX = gp.tileSize * 38;
		gp.monster[mapNum][i].worldY = gp.tileSize * 42;
	}
	
	public void setInteractiveTile() {
		int mapNum = 0;
		int i = 0;
		
		gp.iTile[mapNum][i] = new IT_DryTree(gp, 27, 12);
		
		i++;
		gp.iTile[mapNum][i] = new IT_DryTree(gp, 28, 12);
		
		i++;
		gp.iTile[mapNum][i] = new IT_DryTree(gp, 29, 12);
		
		i++;
		gp.iTile[mapNum][i] = new IT_DryTree(gp, 30, 12);
		
		i++;
		gp.iTile[mapNum][i] = new IT_DryTree(gp, 31, 12);
		
		i++;
		gp.iTile[mapNum][i] = new IT_DryTree(gp, 32, 12);
		
		i++;
		gp.iTile[mapNum][i] = new IT_DryTree(gp, 33, 12);
	}
}
