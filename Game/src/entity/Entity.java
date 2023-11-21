package entity;

import java.awt.Rectangle;
import java.awt.image.BufferedImage;

public class Entity {
	public int worldX, worldY;
	public int speed;
	
//	1 and 2 are front and back
//	0 is idle
	public BufferedImage up0, up1, up2, down0, down1, down2, left0, left1, left2, right0, right1, right2;
	public String direction;
	
	public int spriteCounter = 0;
	public int spriteNum = 1;
	
	public Rectangle solidArea;
	
	public boolean collisionOn = false;
}
