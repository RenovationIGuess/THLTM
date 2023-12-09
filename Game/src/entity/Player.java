package entity;

//import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.image.BufferedImage;
import java.io.IOException;

import javax.imageio.ImageIO;

import main.GamePanel;
import main.KeyHandler;
import main.UtilityTool;

public class Player extends Entity {
	GamePanel gp;
	KeyHandler keyH;
	
	public final int screenX;
	public final int screenY;
	
	public int hasKey = 0;
	
	public Player(GamePanel gp, KeyHandler keyH) {
		this.gp = gp;
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
		
		setDefaultValues();
		getPlayerImage();
	}
	
	public void setDefaultValues() {
		worldX = gp.tileSize * 23;
		worldY = gp.tileSize * 21;
		speed = 4;
		direction = "down";
	}
	
	public void getPlayerImage() {
		up0 = setup("bs_up_0");
		up1 = setup("bs_up_1");
		up2 = setup("bs_up_2");
		
		down0 = setup("bs_down_0");
		down1 = setup("bs_down_1");
		down2 = setup("bs_down_2");
		
		left0 = setup("bs_left_0");
		left1 = setup("bs_left_1");
		left2 = setup("bs_left_2");
		
		right0 = setup("bs_right_0");
		right1 = setup("bs_right_1");
		right2 = setup("bs_right_2");
	}
	
	public BufferedImage setup(String imageName) {
		UtilityTool uTool = new UtilityTool();
		BufferedImage image = null;
		
		try {
			image = ImageIO.read(getClass().getResourceAsStream("/player/" + imageName + ".png"));
			image = uTool.scaleImage(image, gp.tileSize, gp.tileSize);
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		return image;
	}
	
	public void update() {
		if (
				keyH.upPressed == true || 
				keyH.downPressed == true || 
				keyH.leftPressed == true || 
				keyH.rightPressed == true) 
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
			
//			IF COLLISION is false, player can move
			if (collisionOn == false) {
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
			
	//		Because we are using 144 FPS, so every 24 frames we'll re-draw the player once 
			spriteCounter++;
			if (spriteCounter > 24) {
				if (spriteNum == 0) {
					spriteNum = 1;
				}
				else if (spriteNum == 1) {
					spriteNum = 2;
				}
				else if (spriteNum == 2) {
					spriteNum = 0;
				}
				spriteCounter = 0;
			}
		} else {
//			If user | player did not press any keys
			spriteNum = 0;
		}
	}
	
	public void pickUpObject(int i) {
//		Didn't touch any object <=> i == 999
		if (i != 999) {
//			gp.obj[i] = null;
			String objectName = gp.obj[i].name;
			
			switch(objectName) {
			case "Key":
				gp.playSE(1);
				hasKey++;
				gp.obj[i] = null;
				gp.ui.showMessage("Key obtained!");
				break;
			case "Door":
				gp.playSE(4);
				if (hasKey > 0) {
					gp.obj[i] = null;
					hasKey--;
					gp.ui.showMessage("Door opened!");
				} else {
					gp.ui.showMessage("You need a key!");
				}
				System.out.println("Key: " + hasKey);
				break;
			case "Boots":
				gp.playSE(2);
				speed += 1;
				gp.obj[i] = null;
				gp.ui.showMessage("Speed boost +1!");
				break;
			case "Chest":
				gp.ui.gameFinished = true;
				gp.stopMusic();
				gp.playSE(3);
				break;
			}
		}
	}
	
	public void draw(Graphics2D g2) {
//		g2.setColor(Color.white);
//		g2.fillRect(x, y, gp.tileSize, gp.tileSize);
		
		BufferedImage image = null;
		
		switch (direction) {
			case "up":
				if (spriteNum == 0) {
					image = up0;
				}
				if (spriteNum == 1) {
					image = up1;
				}
				if (spriteNum == 2) {
					image = up2;
				}
				break;
			case "down":
				if (spriteNum == 0) {
					image = down0;
				}
				if (spriteNum == 1) {
					image = down1;
				}
				if (spriteNum == 2) {
					image = down2;
				}
				break;
			case "left":
				if (spriteNum == 0) {
					image = left0;
				}
				if (spriteNum == 1) {
					image = left1;
				}
				if (spriteNum == 2) {
					image = left2;
				}
				break;
			case "right":
				if (spriteNum == 0) {
					image = right0;
				}
				if (spriteNum == 1) {
					image = right1;
				}
				if (spriteNum == 2) {
					image = right2;
				}
				break;
		}
		
		g2.drawImage(image, screenX, screenY, null);
//		g2.drawImage(image, screenX, screenY, gp.tileSize, gp.tileSize, null);
	}
}
