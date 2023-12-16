package data;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

import entity.Entity;
import main.GamePanel;
import object.OBJ_Axe;
import object.OBJ_Boots;
import object.OBJ_Chest;
import object.OBJ_Coin_Bronze;
import object.OBJ_Door;
import object.OBJ_Heart;
import object.OBJ_Key;
import object.OBJ_Lantern;
import object.OBJ_ManaCrystal;
import object.OBJ_Potion_Red;
import object.OBJ_Shield_Blue;
import object.OBJ_Shield_Wood;
import object.OBJ_Sword_Normal;
import object.OBJ_Tent;

public class SaveLoad {
	GamePanel gp;
	
	public SaveLoad(GamePanel gp) {
		this.gp = gp;
	}
	
	public void save() {
		try {
			ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(new File("save.dat")));
			
			DataStorage ds = new DataStorage();
			
			ds.maxLife = gp.player.maxLife;
			ds.level = gp.player.level;
			ds.life = gp.player.life;
			ds.strength = gp.player.strength;
			ds.mana = gp.player.mana;
			ds.maxMana = gp.player.maxMana;
			ds.dexterity = gp.player.dexterity;
			ds.exp = gp.player.exp;
			ds.nextLevelExp = gp.player.nextLevelExp;
			ds.coin = gp.player.coin;
			
			for (int i = 0; i < gp.player.inventory.size(); ++i) {
				ds.itemNames.add(gp.player.inventory.get(i).name);
				ds.itemAmounts.add(gp.player.inventory.get(i).amount);
			}
			
//			Player equipment
			ds.currentShieldSlot = gp.player.getCurrentShieldSlot();
			ds.currentWeaponSlot = gp.player.getCurrentWeaponSlot();
			
//			Objs on map
			ds.mapObjectNames = new String[gp.maxMap][gp.obj[1].length];
			ds.mapObjectWorldX = new int[gp.maxMap][gp.obj[1].length];
			ds.mapObjectWorldY = new int[gp.maxMap][gp.obj[1].length];
			ds.mapObjectLootNames = new String[gp.maxMap][gp.obj[1].length];
			ds.mapObjectOpened = new boolean[gp.maxMap][gp.obj[1].length];
			
			for (int mapNum = 0; mapNum < gp.maxMap; ++mapNum) {
				for (int i = 0; i < gp.obj[1].length; ++i) {
					if (gp.obj[mapNum][i] == null) {
						ds.mapObjectNames[mapNum][i] = "NA";
					}
					else {
						ds.mapObjectNames[mapNum][i] = gp.obj[mapNum][i].name;
						ds.mapObjectWorldX[mapNum][i] = gp.obj[mapNum][i].worldX;
						ds.mapObjectWorldY[mapNum][i] = gp.obj[mapNum][i].worldY;
						
						if (gp.obj[mapNum][i].loot != null) {
							ds.mapObjectLootNames[mapNum][i] = gp.obj[mapNum][i].loot.name;
						}
						
						ds.mapObjectOpened[mapNum][i] = gp.obj[mapNum][i].opened;
					}
				}
			}
			
//			Write the ds object
			oos.writeObject(ds);
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
	public void load() {
		try {
			ObjectInputStream ois = new ObjectInputStream(new FileInputStream(new File("save.dat")));
			
	//		Read the ds object
			DataStorage ds = (DataStorage)ois.readObject();
			
			gp.player.maxLife = ds.maxLife;
			gp.player.life = ds.life;
			gp.player.level = ds.level;
			gp.player.strength = ds.strength;
			gp.player.mana = ds.mana;
			gp.player.maxMana = ds.maxMana;
			gp.player.dexterity = ds.dexterity;
			gp.player.exp = ds.exp;
			gp.player.nextLevelExp = ds.nextLevelExp;
			gp.player.coin = ds.coin;
			
//			Player inventory
			gp.player.inventory.clear();
			for (int i = 0; i < ds.itemNames.size(); ++i) {
				gp.player.inventory.add(gp.eGenerator.getObject(ds.itemNames.get(i)));
				gp.player.inventory.get(i).amount = ds.itemAmounts.get(i);
			}
			
//			Player equipment
			gp.player.currentWeapon = gp.player.inventory.get(ds.currentWeaponSlot);
			gp.player.currentShield = gp.player.inventory.get(ds.currentShieldSlot);
			gp.player.getAttack();
			gp.player.getDefense();
			gp.player.getAttackImage();
			
//			Objs on map
			for (int mapNum = 0; mapNum < gp.maxMap; ++mapNum) {
				for (int i = 0; i < gp.obj[1].length; ++i) {
					if (ds.mapObjectNames[mapNum][i].equals("NA")) {
						gp.obj[mapNum][i] = null;
					} 
					else {
						gp.obj[mapNum][i] = gp.eGenerator.getObject(ds.mapObjectNames[mapNum][i]);
						gp.obj[mapNum][i].worldX = ds.mapObjectWorldX[mapNum][i];
						gp.obj[mapNum][i].worldY = ds.mapObjectWorldY[mapNum][i];
						
						if (ds.mapObjectLootNames[mapNum][i] != null) {
							gp.obj[mapNum][i].setLoot(gp.eGenerator.getObject(ds.mapObjectLootNames[mapNum][i]));
						}
						
						gp.obj[mapNum][i].opened = ds.mapObjectOpened[mapNum][i];
						
						if (gp.obj[mapNum][i].opened == true) {
							gp.obj[mapNum][i].down1 = gp.obj[mapNum][i].image2;
						}
					}
				}
			}
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
