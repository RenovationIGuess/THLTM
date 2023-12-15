package data;

import java.io.Serializable;
import java.util.ArrayList;

public class DataStorage implements Serializable {
//	Player stats
	public int maxLife;
	public int level;
	public int life;
	public int strength;
	public int mana;
	public int maxMana;
	public int dexterity;
	public int exp;
	public int nextLevelExp;
	public int coin;
	
//	Player inventory
	ArrayList<String> itemNames = new ArrayList<>();
	ArrayList<Integer> itemAmounts = new ArrayList<>();
	int currentWeaponSlot;
	int currentShieldSlot;
	
//	Objs on the map
	String mapObjectNames[][];
	int mapObjectWorldX[][];
	int mapObjectWorldY[][];
	String mapObjectLootNames[][];
	boolean mapObjectOpened[][];
}
