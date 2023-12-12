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
import java.util.ArrayList;

import object.OBJ_Heart;
import entity.Entity;

public class UI {
	GamePanel gp;
	Graphics2D g2;
	Font maruMonica, purisaB;
	Font arial_40, arial_80B;
	public boolean messageOn = false;
//	public String message = "";
//	int messageCounter = 0;
	ArrayList<String> message = new ArrayList<>();
	ArrayList<Integer> messageCounter = new ArrayList<>();
	public boolean gameFinished = false;
	double playTime;
	DecimalFormat dFormat = new DecimalFormat("#0.00");
	public String currentDialogue = "";
	public int commandNum = 0;
	public int titleScreenState = 0; // 0: first screen, 1: second screen
	public int slotCol = 0;
	public int slotRow = 0;
	
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
	
	public void addMessage(String text) {
		message.add(text);
		messageCounter.add(0);
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
			drawMessage();
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
		
//		Character state
		if (gp.gameState == gp.characterState) {
			drawCharacterScreen();
			drawInventory();
		}
	}
	
	public void drawInventory() {
		int frameX = gp.tileSize * 9;
		int frameY = gp.tileSize - 20;
		int frameWidth = gp.tileSize * 6;
		int frameHeight = gp.tileSize * 5;
		
		drawSubWindow(frameX, frameY, frameWidth, frameHeight);
		
//		Slots
		final int slotXStart = frameX + 20;
		final int slotYStart = frameY + 20;
		int slotX = slotXStart;
		int slotY = slotYStart;
		int slotSize = gp.tileSize + 3;
		
//		Draw player's items
		for (int i = 0; i < gp.player.inventory.size(); ++i) {
//			Equip cursor
			if (gp.player.inventory.get(i) == gp.player.currentWeapon ||
				gp.player.inventory.get(i) == gp.player.currentShield) 
			{
				g2.setColor(new Color(240, 190, 90));
				g2.fillRoundRect(slotX, slotY, gp.tileSize, gp.tileSize, 10, 10);
			}
			
			g2.drawImage(gp.player.inventory.get(i).down1, slotX, slotY, null);
			
			slotX += slotSize;
			
			if (i == 4 || i == 9 || i == 14) {
				slotX = slotXStart;
				slotY += slotSize;
			}
		}
		
//		Draw cursor
		int cursorX = slotXStart + (slotSize * slotCol);
		int cursorY = slotYStart + (slotSize * slotRow);
		int cursorWidth = gp.tileSize;
		int cursorHeight = gp.tileSize;
		
//		Draw cursor
		g2.setColor(Color.white);
		g2.setStroke(new BasicStroke(3));
		g2.drawRoundRect(cursorX, cursorY, cursorWidth, cursorHeight, 10, 10);
		
//		Description frame
		int dFrameX = frameX;
		int dFrameY = frameY + frameHeight;
		int dFrameWidth = frameWidth;
		int dFrameHeight = gp.tileSize * 3;
		
//		Draw description text
		int textX = dFrameX + 20;
		int textY = dFrameY + gp.tileSize;
		
		g2.setFont(g2.getFont().deriveFont(28F));
		
		int itemIndex = getItemIndexOnSlot();
		
		if (itemIndex < gp.player.inventory.size()) {
			drawSubWindow(dFrameX, dFrameY, dFrameWidth, dFrameHeight);
			
			for (String line : gp.player.inventory.get(itemIndex).description.split("\n")) {
				g2.drawString(line, textX, textY);
				textY += 32;
			}
		}
		
	}
	
	public int getItemIndexOnSlot() {
		int itemIndex = slotCol + (slotRow * 5);
		return itemIndex;
	}
	
	public void drawMessage() {
		int messageX = gp.tileSize;
		int messageY = gp.tileSize * 4;
		g2.setFont(g2.getFont().deriveFont(Font.BOLD, 32F));
		
		for (int i = 0; i < message.size(); ++i) {
			if (message.get(i) != null) {
				g2.setColor(Color.black);
				g2.drawString(message.get(i), messageX + 2, messageY + 2);
				
				g2.setColor(Color.white);
				g2.drawString(message.get(i), messageX, messageY);
				
				int counter = messageCounter.get(i) + 1;
				messageCounter.set(i, counter);
				
				messageY += 50;
				
				if (messageCounter.get(i) > 144 * 3) {
					message.remove(i);
					messageCounter.remove(i);
				}
			}
		}
		
	}
	
	public void drawCharacterScreen() {
//		Create a frame
		final int frameX = gp.tileSize - 12;
		final int frameY = gp.tileSize - 20;
		final int frameWidth = gp.tileSize * 5 + 20;
		final int frameHeight = gp.tileSize * 10 + 40;
		
		drawSubWindow(frameX, frameY, frameWidth, frameHeight);
		
//		Text
		g2.setColor(Color.white);
		g2.setFont(g2.getFont().deriveFont(32F));
		
		int textX = frameX + 20;
		int textY = frameY + gp.tileSize;
		final int lineHeight = 40;
		
//		NAMES
		g2.drawString("Level: ", textX, textY);
		textY += lineHeight;
		
		g2.drawString("Life: ", textX, textY);
		textY += lineHeight;
		
		g2.drawString("Strength: ", textX, textY);
		textY += lineHeight;

		g2.drawString("Dexterity: ", textX, textY);
		textY += lineHeight;
		
		g2.drawString("Attack: ", textX, textY);
		textY += lineHeight;
		
		g2.drawString("Defense: ", textX, textY);
		textY += lineHeight;
		
		g2.drawString("Exp: ", textX, textY);
		textY += lineHeight;
		
		g2.drawString("Next Level Exp: ", textX, textY);
		textY += lineHeight;

		g2.drawString("Coin: ", textX, textY);
		textY += lineHeight + 12;
		
		g2.drawString("Weapon: ", textX, textY);
		textY += lineHeight + 16;
		
		g2.drawString("Shield: ", textX, textY);
		textY += lineHeight;
		
//		VALUES
		int tailX = (frameX + frameWidth) - 30;
//		Reset textY
		textY = frameY + gp.tileSize;
		String value;
		
		value = String.valueOf(gp.player.level);
		textX = getXForAlignToRightText(value, tailX);
		g2.drawString(value, textX, textY);
		textY += lineHeight;
		
		value = String.valueOf(gp.player.life + "/" + gp.player.maxLife);
		textX = getXForAlignToRightText(value, tailX);
		g2.drawString(value, textX, textY);
		textY += lineHeight;
		
		value = String.valueOf(gp.player.strength);
		textX = getXForAlignToRightText(value, tailX);
		g2.drawString(value, textX, textY);
		textY += lineHeight;
		
		value = String.valueOf(gp.player.dexterity);
		textX = getXForAlignToRightText(value, tailX);
		g2.drawString(value, textX, textY);
		textY += lineHeight;
		
		value = String.valueOf(gp.player.attack);
		textX = getXForAlignToRightText(value, tailX);
		g2.drawString(value, textX, textY);
		textY += lineHeight;
		
		value = String.valueOf(gp.player.defense);
		textX = getXForAlignToRightText(value, tailX);
		g2.drawString(value, textX, textY);
		textY += lineHeight;
		
		value = String.valueOf(gp.player.exp);
		textX = getXForAlignToRightText(value, tailX);
		g2.drawString(value, textX, textY);
		textY += lineHeight;
		
		value = String.valueOf(gp.player.nextLevelExp);
		textX = getXForAlignToRightText(value, tailX);
		g2.drawString(value, textX, textY);
		textY += lineHeight;
		
		value = String.valueOf(gp.player.coin);
		textX = getXForAlignToRightText(value, tailX);
		g2.drawString(value, textX, textY);
		textY += lineHeight;
		
		g2.drawImage(gp.player.currentWeapon.down1, tailX - gp.tileSize, textY - 20, null);
		textY += gp.tileSize + 16;
		
		g2.drawImage(gp.player.currentShield.down1, tailX - gp.tileSize, textY - 30, null);		
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
	
	public int getXForAlignToRightText(String text, int tailX) {
		int length = (int)g2.getFontMetrics().getStringBounds(text, g2).getWidth();
		int x = tailX - length;
		
		return x;
	}
}
