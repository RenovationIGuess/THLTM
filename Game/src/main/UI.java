package main;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Font;
import java.awt.FontFormatException;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.io.InputStream;
import java.text.DecimalFormat;

import object.OBJ_Heart;
import entity.Entity;

public class UI {
	GamePanel gp;
	Graphics2D g2;
	Font maruMonica, purisaB;
	Font arial_40, arial_80B;
	public boolean messageOn = false;
	public String message = "";
	int messageCounter = 0;
	public boolean gameFinished = false;
	double playTime;
	DecimalFormat dFormat = new DecimalFormat("#0.00");
	public String currentDialogue = "";
	public int commandNum = 0;
	public int titleScreenState = 0; // 0: first screen, 1: second screen
	
//	Character status
	BufferedImage heart_full, heart_half, heart_blank;
	
	public UI(GamePanel gp) {
		this.gp = gp;
		
		arial_40 = new Font("Arial", Font.PLAIN, 40);
		arial_80B = new Font("Arial", Font.BOLD, 80);
		
		try {
			InputStream is = getClass().getResourceAsStream("/font/x12y16pxMaruMonica.ttf");
			maruMonica = Font.createFont(Font.TRUETYPE_FONT, is);
			
			is = getClass().getResourceAsStream("/font/Purisa Bold.ttf");
			purisaB = Font.createFont(Font.TRUETYPE_FONT, is);
		} catch (FontFormatException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
//		Create HUD object
		Entity heart = new OBJ_Heart(gp);
		heart_full = heart.image;
		heart_half = heart.image2;
		heart_blank = heart.image3;
	}
	
	public void showMessage(String text) {
		message = text;
		messageOn = true;
	}
	
	public void draw(Graphics2D g2) {
		this.g2 = g2;
		
		g2.setFont(maruMonica);
		g2.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING, RenderingHints.VALUE_TEXT_ANTIALIAS_ON);
		g2.setColor(Color.white);
		
		if (gp.gameState == gp.titleState) {
			drawTitleScreen();
		}
		
		if (gp.gameState == gp.playState) {
//			TODO:
			drawPlayerLife();
		}
		
		if (gp.gameState == gp.pauseState) {
//			TODO:
			drawPlayerLife();
			drawPauseScreen();
		}
		
		if (gp.gameState == gp.dialogueState) {
			drawPlayerLife();
			drawDialogueScreen();
		}
	}
	
	public void drawPlayerLife() {
//		gp.player.life = 3;
		
		int x = gp.tileSize / 2;
		int y = gp.tileSize / 2;
		int i = 0;
		
//		Draw Blank Heart
		while (i < gp.player.maxLife / 2) {
			g2.drawImage(heart_blank, x, y, null);
			i++;
			x += gp.tileSize;
		}
		
		x = gp.tileSize / 2;
		y = gp.tileSize / 2;
		i = 0;
		
//		Draw currentLife
		while (i < gp.player.life) {
			g2.drawImage(heart_half, x, y, null);
			i++;
			if (i < gp.player.life) {
				g2.drawImage(heart_full, x, y, null);
			}
			i++;
			x += gp.tileSize;
		}
	}
	
	public void drawTitleScreen() {
		if (titleScreenState == 0) {
			g2.setColor(new Color(0, 0, 0));
			g2.fillRect(0, 0, gp.screenWidth, gp.screenHeight);
			
//			TITLE NAME
			g2.setFont(g2.getFont().deriveFont(Font.BOLD, 96F));
			
			String text = "Blue Boy Adventure";
			
			int x = getXForCenteredText(text);
			int y = gp.tileSize * 3;
			
//			SHADOW
			g2.setColor(Color.gray);
			g2.drawString(text, x + 5, y + 5);
//			MAIN COLOR
			g2.setColor(Color.white);
			g2.drawString(text, x, y);
			
//			BLUE BOY IMAGE
			x = gp.screenWidth / 2 - (gp.tileSize * 2) / 2;
			y += gp.tileSize * 2;
			g2.drawImage(gp.player.down1, x, y, gp.tileSize * 2, gp.tileSize * 2, null);
			
//			MENU
			g2.setFont(g2.getFont().deriveFont(Font.BOLD, 48F));
			text = "NEW GAME";
			x = getXForCenteredText(text);
			y += gp.tileSize * 3.5;
			g2.drawString(text, x, y);
			
			if (commandNum == 0) {
				g2.drawString(">", x - gp.tileSize, y);
			}
			
			text = "LOAD GAME";
			x = getXForCenteredText(text);
			y += gp.tileSize + 16;
			g2.drawString(text, x, y);

			if (commandNum == 1) {
				g2.drawString(">", x - gp.tileSize, y);
			}
			
			text = "QUIT";
			x = getXForCenteredText(text);
			y += gp.tileSize + 16;
			g2.drawString(text, x, y);
			
			if (commandNum == 2) {
				g2.drawString(">", x - gp.tileSize, y);
			}
		}
		else if (titleScreenState == 1) {
			g2.setColor(Color.white);
			g2.setFont(g2.getFont().deriveFont(42F));
			
			String text = "Select your class!";
			int x = getXForCenteredText(text);
			int y = gp.tileSize * 3;
			g2.drawString(text, x, y);
			
			text = "Fighter";
			x = getXForCenteredText(text);
			y += gp.tileSize * 3;
			g2.drawString(text, x, y);
			
			if (commandNum == 0) {
				g2.drawString(">", x - gp.tileSize, y);
			}
			
			text = "Thief";
			x = getXForCenteredText(text);
			y += gp.tileSize + 12;
			g2.drawString(text, x, y);
			
			if (commandNum == 1) {
				g2.drawString(">", x - gp.tileSize, y);
			}
			
			text = "Sorcerer";
			x = getXForCenteredText(text);
			y += gp.tileSize + 12;
			g2.drawString(text, x, y);
			
			if (commandNum == 2) {
				g2.drawString(">", x - gp.tileSize, y);
			}
			
			text = "Back";
			x = getXForCenteredText(text);
			y += gp.tileSize + 12;
			g2.drawString(text, x, y);
			
			if (commandNum == 3) {
				g2.drawString(">", x - gp.tileSize, y);
			}
		}
	}
	
	public void drawPauseScreen() {
		g2.setFont(g2.getFont().deriveFont(Font.PLAIN, 80F));
		String text = "PAUSED";
		
		int x = getXForCenteredText(text);
		int y = gp.screenHeight / 2;
		
		g2.drawString(text, x, y);
	}
	
	public void drawDialogueScreen() {
		// WINDOW
		int x = gp.tileSize * 2;
		int y = gp.tileSize / 2;
		int width = gp.screenWidth - (gp.tileSize * 4);
		int height = gp.tileSize * 3;
		
		drawSubWindow(x, y, width, height);
		
		g2.setFont(g2.getFont().deriveFont(Font.PLAIN, 24F));
		x += gp.tileSize / 2;
		y += gp.tileSize;
		
		for (String line : currentDialogue.split("\n")) {
			g2.drawString(line, x, y);
			y += 40;
		}
//		g2.drawString(currentDialogue, x, y);
	}
	
	public void drawSubWindow(int x, int y, int width, int height) {
		Color c = new Color(0, 0, 0, 210);
		g2.setColor(c);
		
		g2.fillRoundRect(x, y, width, height, 35, 35);
		
		c = new Color(255, 255, 255);
		g2.setColor(c);
		g2.setStroke(new BasicStroke(5));
		g2.drawRoundRect(x + 5, y + 5, width - 10, height - 10, 25, 25);
	}
	
	public int getXForCenteredText(String text) {
		int length = (int)g2.getFontMetrics().getStringBounds(text, g2).getWidth();
		int x = gp.screenWidth / 2 - length / 2;
		
		return x;
	}
}
