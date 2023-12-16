package monster;

import java.util.Random;

import data.Progress;
import entity.Entity;
import main.GamePanel;
import object.OBJ_Coin_Bronze;
import object.OBJ_Door_Iron;
import object.OBJ_Heart;
import object.OBJ_ManaCrystal;

public class MON_SkeletonLord extends Entity {
	GamePanel gp;
	public final static String monName = "Skeleton Lord";
	
	public MON_SkeletonLord(GamePanel gp) {
		super(gp);
		
		this.gp = gp;
		
		type = type_monster;
		boss = true;
		name = monName;
		defaultSpeed = 1;
		speed = defaultSpeed;
		maxLife = 500;
		life = maxLife;
		attack = 20;
		defense = 10;
		exp = 999;
		knockBackPower = 5;
		sleep = true;

		int size = gp.tileSize * 5;
		solidArea.x = 48;
		solidArea.y = 48;
		solidArea.width = size - 48 * 2;
		solidArea.height = size - 48;
		solidAreaDefaultX = solidArea.x;
		solidAreaDefaultY = solidArea.y;
		attackArea.width = 170;
		attackArea.height = 170;
		motion1_duration = 25;
		motion2_duration = 50;
		
		getImage();
		getAttackImage();
		setDialogue();
	}
	
	public void setDialogue() {
		dialogues[0][0] = "Don't look at me... I'm so ugly T.T";
		dialogues[0][1] = "This is the result of coding too much.";
		dialogues[0][2] = "But luckily you've came, now you'll be my replacement!";
	}
	
	public void getImage() {
		int i = 5;

		if (inRage == false) {
			up1 = setup("/monster/skeletonlord_up_1", gp.tileSize * i, gp.tileSize * i);
			up2 = setup("/monster/skeletonlord_up_2", gp.tileSize * i, gp.tileSize * i);
			
			down1 = setup("/monster/skeletonlord_down_1", gp.tileSize * i, gp.tileSize * i);
			down2 = setup("/monster/skeletonlord_down_2", gp.tileSize * i, gp.tileSize * i);
			
			right1 = setup("/monster/skeletonlord_right_1", gp.tileSize * i, gp.tileSize * i);
			right2 = setup("/monster/skeletonlord_right_2", gp.tileSize * i, gp.tileSize * i);
			
			left1 = setup("/monster/skeletonlord_left_1", gp.tileSize * i, gp.tileSize * i);
			left2 = setup("/monster/skeletonlord_left_2", gp.tileSize * i, gp.tileSize * i);
		}
		else if (inRage == true) {
			up2 = setup("/monster/skeletonlord_phase2_up_2", gp.tileSize * i, gp.tileSize * i);
			up1 = setup("/monster/skeletonlord_phase2_up_1", gp.tileSize * i, gp.tileSize * i);
			
			down1 = setup("/monster/skeletonlord_phase2_down_1", gp.tileSize * i, gp.tileSize * i);
			down2 = setup("/monster/skeletonlord_phase2_down_2", gp.tileSize * i, gp.tileSize * i);
			
			right1 = setup("/monster/skeletonlord_phase2_right_1", gp.tileSize * i, gp.tileSize * i);
			right2 = setup("/monster/skeletonlord_phase2_right_2", gp.tileSize * i, gp.tileSize * i);
			
			left1 = setup("/monster/skeletonlord_phase2_left_1", gp.tileSize * i, gp.tileSize * i);
			left2 = setup("/monster/skeletonlord_phase2_left_2", gp.tileSize * i, gp.tileSize * i);
		}
	}
	
	public void getAttackImage() {
		int i = 5;

		if (inRage == false) {
			attackUp1 = setup("/monster/skeletonlord_attack_up_1", gp.tileSize * i, gp.tileSize * i * 2);
			attackUp2 = setup("/monster/skeletonlord_attack_up_2", gp.tileSize * i, gp.tileSize * i * 2);
			
			attackDown1 = setup("/monster/skeletonlord_attack_down_1", gp.tileSize * i, gp.tileSize * i * 2);
			attackDown2 = setup("/monster/skeletonlord_attack_down_2", gp.tileSize * i, gp.tileSize * i * 2);
			
			attackRight1 = setup("/monster/skeletonlord_attack_right_1", gp.tileSize * i * 2, gp.tileSize * i);
			attackRight2 = setup("/monster/skeletonlord_attack_right_2", gp.tileSize * i * 2, gp.tileSize * i);
			
			attackLeft1 = setup("/monster/skeletonlord_attack_left_1", gp.tileSize * i * 2, gp.tileSize * i);
			attackLeft2 = setup("/monster/skeletonlord_attack_left_2", gp.tileSize * i * 2, gp.tileSize * i);
		}
		else if (inRage == true) {
			attackUp1 = setup("/monster/skeletonlord_phase2_attack_up_1", gp.tileSize * i, gp.tileSize * i * 2);
			attackUp2 = setup("/monster/skeletonlord_phase2_attack_up_2", gp.tileSize * i, gp.tileSize * i * 2);
			
			attackDown1 = setup("/monster/skeletonlord_phase2_attack_down_1", gp.tileSize * i, gp.tileSize * i * 2);
			attackDown2 = setup("/monster/skeletonlord_phase2_attack_down_2", gp.tileSize * i, gp.tileSize * i * 2);
			
			attackRight1 = setup("/monster/skeletonlord_phase2_attack_right_1", gp.tileSize * i * 2, gp.tileSize * i);
			attackRight2 = setup("/monster/skeletonlord_phase2_attack_right_2", gp.tileSize * i * 2, gp.tileSize * i);
			
			attackLeft1 = setup("/monster/skeletonlord_phase2_attack_left_1", gp.tileSize * i * 2, gp.tileSize * i);
			attackLeft2 = setup("/monster/skeletonlord_phase2_attack_left_2", gp.tileSize * i * 2, gp.tileSize * i);
		}
	}
	
	public void setAction() {	
		if (inRage == false && life < maxLife/2) {
			inRage = true;
			getImage();
			getAttackImage();
			defaultSpeed++;
			speed = defaultSpeed;
			attack *= 2;
		}
		if (getTileDistance(gp.player) < 10) {
			moveTowardPlayer(144);
		}
		else {
//			Get a random direction
			getRandomDirection(144 * 3);
		}
		
//		Check if it attacks
		if (attacking == false) {
			checkAttackOrNot(144, gp.tileSize*7, gp.tileSize*5);
		}
	}
	
	public void damageReaction() {
		actionLockCounter = 0;
	}
	
	public void checkDrop() {
		gp.bossBattleOn = false;
		Progress.skeletonLordDefeated = true;
		
//		Restore the previous music
		gp.stopMusic();
		gp.playMusic(21);
		
//		Remove the iron door
		for (int i = 0; i < gp.obj[1].length; ++i) {
			if (gp.obj[gp.currentMap][i] != null &&
					gp.obj[gp.currentMap][i].name.equals(OBJ_Door_Iron.objName))
			{
				gp.playSE(19);
				gp.obj[gp.currentMap][i] = null;
			}
		}
		
//		Cast a die
		int i = new Random().nextInt(100) + 1;
		
//		Set the monster drop
		if (i < 50) {
			dropItem(new OBJ_Coin_Bronze(gp));
		}
		if (i >= 50 && i < 75) {
			dropItem(new OBJ_Heart(gp));
		}
		if (i >= 75 && i <= 100) {
			dropItem(new OBJ_ManaCrystal(gp));
		}
	}
}
