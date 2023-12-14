package entity;

import java.awt.AlphaComposite;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.image.BufferedImage;
import java.util.ArrayList;

import main.GamePanel;
import main.KeyHandler;
import object.OBJ_Fireball;
import object.OBJ_Key;
import object.OBJ_Shield_Wood;
import object.OBJ_Sword_Normal;

public class Player extends Entity {
	KeyHandler keyH;
	
	public final int screenX;
	public final int screenY;
	
	int standCounter = 0;
	public boolean attackCanceled = false;
	public boolean lightUpdated = false;
	
	public Player(GamePanel gp, KeyHandler keyH) {
		super(gp);
		
		this.keyH = keyH;
		
		screenX = gp.screenWidth / 2 - (gp.tileSize / 2);
		screenY = gp.screenHeight / 2 - (gp.tileSize / 2);
		
		solidArea = new Rectangle();
		solidArea.x = 8;
		solidArea.y = 16;
		solidAreaDefaultX = solidArea.x;
		solidAreaDefaultY = solidArea.y;
		solidArea.width = 32;
		solidArea.height = 32;
		
//		attackArea.width = 36;
//		attackArea.height = 36;
		
		setDefaultValues();
		getPlayerImage();
		getPlayerAttackImage();
		setItems();
	}
	
	public void setDefaultValues() {
		worldX = gp.tileSize * 23;
		worldY = gp.tileSize * 21;
//		worldX = gp.tileSize * 12;
//		worldY = gp.tileSize * 13;
//		gp.currentMap = 1;
		defaultSpeed = 2;
		speed = defaultSpeed;
		direction = "down";
		
//		Player status;
		maxLife = 6;
		life = maxLife;
		level = 1;
		ammo = 10;
		maxMana = 4;
		mana = maxMana;
		strength = 1; // The more strength char has, the more dmg char does
		dexterity = 1; // The higher it is, the less dmg received
		exp = 0;
		nextLevelExp = 5;
		coin = 1000;
		currentWeapon = new OBJ_Sword_Normal(gp);
		currentShield = new OBJ_Shield_Wood(gp);
		projectile = new OBJ_Fireball(gp);
		attack = getAttack(); // decided by strength and weapon
		defense = getDefense(); // decided by dexterity and shield
	}
	
	public void setDefaultPositions() {
		worldX = gp.tileSize * 23;
		worldY = gp.tileSize * 21;
		direction = "down";
	}
	
	public void restoreLifeAndMana() {
		life = maxLife;
		mana = maxMana;
		invincible = false;
	}
	
	public void setItems() {
		inventory.clear();
		inventory.add(currentWeapon);
		inventory.add(currentShield);
		inventory.add(new OBJ_Key(gp));
	}
	
	public int getAttack() {
		attackArea = currentWeapon.attackArea;
		motion1_duration = currentWeapon.motion1_duration;
		motion2_duration = currentWeapon.motion2_duration;
		return attack = strength * currentWeapon.attackValue;
	}
	
	public int getDefense() {
		return defense = dexterity * currentShield.defenseValue;
	}
	
	public void getPlayerImage() {
		up1 = setup("/player/boy_up_1", gp.tileSize, gp.tileSize);
		up2 = setup("/player/boy_up_2", gp.tileSize, gp.tileSize);
		
		down1 = setup("/player/boy_down_1", gp.tileSize, gp.tileSize);
		down2 = setup("/player/boy_down_2", gp.tileSize, gp.tileSize);
		
		left1 = setup("/player/boy_left_1", gp.tileSize, gp.tileSize);
		left2 = setup("/player/boy_left_2", gp.tileSize, gp.tileSize);
		
		right1 = setup("/player/boy_right_1", gp.tileSize, gp.tileSize);
		right2 = setup("/player/boy_right_2", gp.tileSize, gp.tileSize);
	}
	
	public void getSleepingImage(BufferedImage image) {
		up1 = image;
		up2 = image;
		
		down1 = image;
		down2 = image;
		
		left1 = image;
		left2 = image;
		
		right1 = image;
		right2 = image;
	}
	
	public void getPlayerAttackImage() {
		if (currentWeapon.type == type_sword) {
			attackUp1 = setup("/player/boy_attack_up_1", gp.tileSize, gp.tileSize * 2);
			attackUp2 = setup("/player/boy_attack_up_2", gp.tileSize, gp.tileSize * 2);
			
			attackDown1 = setup("/player/boy_attack_down_1", gp.tileSize, gp.tileSize * 2);
			attackDown2 = setup("/player/boy_attack_down_2", gp.tileSize, gp.tileSize * 2);
			
			attackRight1 = setup("/player/boy_attack_right_1", gp.tileSize * 2, gp.tileSize);
			attackRight2 = setup("/player/boy_attack_right_2", gp.tileSize * 2, gp.tileSize);
			
			attackLeft1 = setup("/player/boy_attack_left_1", gp.tileSize * 2, gp.tileSize);
			attackLeft2 = setup("/player/boy_attack_left_2", gp.tileSize * 2, gp.tileSize);
		} else if (currentWeapon.type == type_axe) {
			attackUp1 = setup("/player/boy_axe_up_1", gp.tileSize, gp.tileSize * 2);
			attackUp2 = setup("/player/boy_axe_up_2", gp.tileSize, gp.tileSize * 2);
			
			attackDown1 = setup("/player/boy_axe_down_1", gp.tileSize, gp.tileSize * 2);
			attackDown2 = setup("/player/boy_axe_down_2", gp.tileSize, gp.tileSize * 2);
			
			attackRight1 = setup("/player/boy_axe_right_1", gp.tileSize * 2, gp.tileSize);
			attackRight2 = setup("/player/boy_axe_right_2", gp.tileSize * 2, gp.tileSize);
			
			attackLeft1 = setup("/player/boy_axe_left_1", gp.tileSize * 2, gp.tileSize);
			attackLeft2 = setup("/player/boy_axe_left_2", gp.tileSize * 2, gp.tileSize);
		}
		
		
	}
	
	public void update() {
		if (attacking == true) {
			attacking();
		}
		else if (
				keyH.upPressed == true || 
				keyH.downPressed == true || 
				keyH.leftPressed == true || 
				keyH.rightPressed == true ||
				keyH.enterPressed == true)
		{
			if (keyH.upPressed == true) {
				direction = "up";
			} else if (keyH.downPressed == true) {
				direction = "down";
			} else if (keyH.leftPressed == true) {
				direction = "left";
			} else if (keyH.rightPressed == true) {
				direction = "right";
			}
			
//			Check tile collision
			collisionOn = false;
			gp.cChecker.checkTile(this);
			
//			Check object collision
			int objIndex = gp.cChecker.checkObject(this, true);
			pickUpObject(objIndex);
			
//			Check NPCs collision
			int npcIndex = gp.cChecker.checkEntity(this, gp.npc);
			interactNPC(npcIndex);
			
//			Check monster collision
			int monsterIndex = gp.cChecker.checkEntity(this, gp.monster);
			contactMonster(monsterIndex);
			
//			Check interactive tile collision
			int iTileIndex = gp.cChecker.checkEntity(this, gp.iTile);
			
//			Check event
			gp.eHandler.checkEvent();
			
//			IF COLLISION is false, player can move
			if (collisionOn == false && keyH.enterPressed == false) {
				switch (direction) {
				case "up":
					worldY -= speed;
					break;
				case "down":
					worldY += speed;
					break;
				case "left":
					worldX -= speed;
					break;
				case "right":
					worldX += speed;
					break;
				}
			}
			
			if (keyH.enterPressed == true && attackCanceled == false) {
				gp.playSE(7);
				attacking = true;
				spriteCounter = 0;
			}
			
			attackCanceled = false;
			gp.keyH.enterPressed = false;
			
	//		Because we are using 144 FPS, so every 24 frames we'll re-draw the player once 
			spriteCounter++;
			if (spriteCounter > 24) {
//				if (spriteNum == 0) {
//					spriteNum = 1;
//				}
//				else 
				if (spriteNum == 1) {
					spriteNum = 2;
				}
				else if (spriteNum == 2) {
					spriteNum = 1;
				}
				spriteCounter = 0;
			}
		} else {
//			If user | player did not press any keys
			standCounter++;
			if (standCounter == 24) {
				spriteNum = 1;
				standCounter = 0;
			}
		}
		
		if (gp.keyH.shotKeyPressed == true && 
				projectile.alive == false && 
				shotAvailableCounter == 72 && 
				projectile.haveResource(this)) 
		{
//			Set default coordinates, direction and user
			projectile.set(worldX, worldY, direction, true, this);
			
//			Subtract cost
			projectile.subtractResource(this);
			
//			Add to the list
			for (int i = 0; i < gp.projectile[1].length; ++i) {
				if (gp.projectile[gp.currentMap][i] == null) {
					gp.projectile[gp.currentMap][i] = projectile;
					break;
				}
			}
			gp.playSE(10);
			
			shotAvailableCounter = 0;
		}
		
//		This needs to be outside of key if statement!
		if (invincible == true) {
			invincibleCounter++;
			if (invincibleCounter > 144) {
				invincible = false;
				invincibleCounter = 0;
			}
		}
		
		if (shotAvailableCounter < 72) {
			shotAvailableCounter++;
		}
		
		if (life > maxLife) {
			life = maxLife;
		}
		
		if (mana > maxMana) {
			mana = maxMana;
		}
		
		if (life <= 0) {
			gp.gameState = gp.gameOverState;
			gp.ui.commandNum = -1;
			gp.stopMusic();
			gp.playSE(12);
		}
	}
	
	public void damageProjectile(int i) {
		if (i != 999) {
			Entity projectile = gp.projectile[gp.currentMap][i];
			projectile.alive = false;
			generateParticle(projectile, projectile);
		}
	}
	
	public void damageInteractiveTile(int i) {
		if (i != 999 && 
				gp.iTile[gp.currentMap][i].destructible && 
				gp.iTile[gp.currentMap][i].isCorrectItem(this) &&
				gp.iTile[gp.currentMap][i].invincible == false) 
		{
			gp.iTile[gp.currentMap][i].playSE();
			gp.iTile[gp.currentMap][i].life--;
			gp.iTile[gp.currentMap][i].invincible = true;
			
//			Generate particle
			generateParticle(gp.iTile[gp.currentMap][i], gp.iTile[gp.currentMap][i]);
			
			if (gp.iTile[gp.currentMap][i].life <= 0) {
				gp.iTile[gp.currentMap][i] = gp.iTile[gp.currentMap][i].getDestroyedItem();
			}
		}
	}
	
	public void pickUpObject(int i) {
//		Didn't touch any object <=> i == 999
		if (i != 999) {
//			TODO:
			if (gp.obj[gp.currentMap][i].type == type_pickUpOnly) {
				gp.obj[gp.currentMap][i].use(this);
				gp.obj[gp.currentMap][i] = null;
			} 
			else if (gp.obj[gp.currentMap][i].type == type_obstacle) {
				if (keyH.enterPressed == true) {
					attackCanceled = true;
					gp.obj[gp.currentMap][i].interact();
				}
			}
 			else {
				String text;
				
				if (canObtainItem(gp.obj[gp.currentMap][i])) {
					gp.playSE(1);
					text = "You picked up " + gp.obj[gp.currentMap][i].name + "!";
				}
				else {
					text = "Your inventory is full!";
				}
				
				gp.ui.addMessage(text);
				gp.obj[gp.currentMap][i] = null;
			}
		}
	}
	
	public void interactNPC(int i) {
		if (gp.keyH.enterPressed) {
			if (i != 999) {
				attackCanceled = true;
				gp.gameState = gp.dialogueState;
				gp.npc[gp.currentMap][i].speak();
			}
//			else {
//				gp.playSE(7);
//				attacking = true;
//			}
		}
//		gp.keyH.enterPressed = false;
	}
	
	public void contactMonster(int i) {
		if (i != 999) {
			if (invincible == false && gp.monster[gp.currentMap][i].dying == false) {
				gp.playSE(6);
				
				int damage = gp.monster[gp.currentMap][i].attack - defense;
				
				if (damage < 0) {
					damage = 0;
				}
				
				life -= damage;
				invincible = true;
			}
		}
	}
	
	public void damageMonster(int i, Entity attacker, int attack, int knockBackPower) {
		if (i != 999) {
//			System.out.println("HIT!");
			if (gp.monster[gp.currentMap][i].invincible == false) {				
				gp.playSE(5);
				
				if (knockBackPower > 0) {
					setKnockBack(gp.monster[gp.currentMap][i], attacker, knockBackPower);
				}
				
				int damage = attack - gp.monster[gp.currentMap][i].defense;
				
				if (damage < 0) {
					damage = 0;
				}
				
				gp.monster[gp.currentMap][i].life -= damage;
				
				gp.ui.addMessage(damage + " damage!");
				
				gp.monster[gp.currentMap][i].invincible = true;
				gp.monster[gp.currentMap][i].damageReaction();
				
				if (gp.monster[gp.currentMap][i].life <= 0) {
					gp.monster[gp.currentMap][i].dying = true;
					gp.ui.addMessage("You killed " + gp.monster[gp.currentMap][i].name + "!");
					exp += gp.monster[gp.currentMap][i].exp;
					gp.ui.addMessage("You gained " + gp.monster[gp.currentMap][i].exp + "exp!");
					checkLevelUp();
				}
			}
		} else {
//			System.out.println("MISS!");
		}
	}
	
	public void checkLevelUp() {
		if (exp >= nextLevelExp) {
			level++;
			nextLevelExp = nextLevelExp * 2;
			maxLife += 2;
			strength++;
			dexterity++;
			attack = getAttack();
			defense = getDefense();
			
			gp.playSE(8);
			gp.gameState = gp.dialogueState;
			gp.ui.currentDialogue = "You are level " + level + " now!\n" + "You feel stronger :))";
		}
	}
	
	public void selectItem() {
		int itemIndex = gp.ui.getItemIndexOnSlot(gp.ui.playerSlotCol, gp.ui.playerSlotRow);
		
		if (itemIndex < inventory.size()) {
			Entity selectedItem = inventory.get(itemIndex);
			
			if (selectedItem.type == type_sword || selectedItem.type == type_axe) {
				currentWeapon = selectedItem;
				attack = getAttack();
				getPlayerAttackImage();
			} else if (selectedItem.type == type_shield) {
				currentShield = selectedItem;
				defense = getDefense();
			}
			
			if (selectedItem.type == type_light) {
				if (currentLight == selectedItem) {
					currentLight = null;
				} 
				else {
					currentLight = selectedItem;
				}
				lightUpdated = true;
			}
			
			if (selectedItem.type == type_consumable) {
//				TODO:
				if (selectedItem.use(this) == true) {
					if (selectedItem.amount > 1) {
						selectedItem.amount--;
					} else inventory.remove(itemIndex);
				}
			}
		}
	}
	
	public int searchItemInInventory(String itemName) {
		int itemIndex = 999;
		
		for (int i = 0; i < inventory.size(); ++i) {
			if (inventory.get(i).name.equals(itemName)) {
				itemIndex = i;
				break;
			}
		}
		
		return itemIndex;
	}
	
	public boolean canObtainItem(Entity item) {
		boolean canObtain = false;
		
//		Check if stackable
		if (item.stackable == true) {
			int index = searchItemInInventory(item.name);
			if (index != 999) {
				inventory.get(index).amount++;
				canObtain = true;
			}
			else {
//				New item - check vacancy
				if (inventory.size() != maxInventorySize) {
					inventory.add(item);
					canObtain = true;
				}
			}
		}
		else {
//			Not stackable
			if (inventory.size() != maxInventorySize) {
				inventory.add(item);
				canObtain = true;
			}
		}
		
		return canObtain;
	}
	
	public void draw(Graphics2D g2) {
//		g2.setColor(Color.white);
//		g2.fillRect(x, y, gp.tileSize, gp.tileSize);
		
		BufferedImage image = null;
		int tempScreenX = screenX;
		int tempScreenY = screenY;
		
		switch (direction) {
			case "up":
				if (attacking == false) {
					if (spriteNum == 1) {
						image = up1;
					}
					if (spriteNum == 2) {
						image = up2;
					}
				} else {
					tempScreenY = screenY - gp.tileSize;
					if (spriteNum == 1) {
						image = attackUp1;
					}
					if (spriteNum == 2) {
						image = attackUp2;
					}
				}
//				if (spriteNum == 0) {
//					image = up0;
//				}
				break;
			case "down":
//				if (spriteNum == 0) {
//					image = down0;
//				}
				if (attacking == false) {
					if (spriteNum == 1) {
						image = down1;
					}
					if (spriteNum == 2) {
						image = down2;
					}
				} else {
					if (spriteNum == 1) {
						image = attackDown1;
					}
					if (spriteNum == 2) {
						image = attackDown2;
					}
				}
				break;
			case "left":
//				if (spriteNum == 0) {
//					image = left0;
//				}
				if (attacking == false) {
					if (spriteNum == 1) {
						image = left1;
					}
					if (spriteNum == 2) {
						image = left2;
					}
				} else {
					tempScreenX = screenX - gp.tileSize;
					if (spriteNum == 1) {
						image = attackLeft1;
					}
					if (spriteNum == 2) {
						image = attackLeft2;
					}
				}
				break;
			case "right":
//				if (spriteNum == 0) {
//					image = right0;
//				}
				if (attacking == false) {
					if (spriteNum == 1) {
						image = right1;
					}
					if (spriteNum == 2) {
						image = right2;
					}
				} else {
					if (spriteNum == 1) {
						image = attackRight1;
					}
					if (spriteNum == 2) {
						image = attackRight2;
					}
				}
				break;
		}
		
		if (invincible == true) {
			g2.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER, 0.4f));
		}
		
		g2.drawImage(image, tempScreenX, tempScreenY, null);
		
//		Reset alpha
		g2.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER, 1f));
		
//		g2.drawImage(image, screenX, screenY, gp.tileSize, gp.tileSize, null);
		
//		Debug
//		g2.setFont(new Font("Arial", Font.PLAIN, 26));
//		g2.setColor(Color.white);
//		g2.drawString("Invincible: " + invincibleCounter, 10, 400);
	}
}
