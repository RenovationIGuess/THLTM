package main;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;

import javax.swing.JPanel;

import entity.Entity;
import entity.Player;
import object.AssetSetter;
import object.SuperObject;
import tiles.TileManager;

public class GamePanel extends JPanel implements Runnable {
	private static final long serialVersionUID = 1L;
	// SCREEN SETTINGS
	// Default size of characters, NPCs, tiles
	final int originalTileSize = 16; // 16x16 tile
	final int scale = 3;
	
	public final int tileSize = originalTileSize * scale; // 48x48 tile
	// Ratio 4:3
	public final int maxScreenCol = 16;
	public final int maxScreenRow = 12;
	public final int screenWidth = tileSize * maxScreenCol;
	public final int screenHeight = tileSize * maxScreenRow;
	
//	WORLD SETTINGS
	public final int maxWorldCol = 50;
	public final int maxWorldRow = 50;
	
//	Redundant - can be removed
	public final int worldWidth = tileSize * maxWorldCol;
	public final int worldHeight = tileSize * maxWorldRow;
	
//	FPS
	int FPS = 144;
	
	TileManager tileM = new TileManager(this);
	public KeyHandler keyH = new KeyHandler(this);
	Sound music = new Sound();
	Sound se = new Sound();
	public CollisionChecker cChecker = new CollisionChecker(this);
	public AssetSetter aSetter = new AssetSetter(this);
	public UI ui = new UI(this);
	Thread gameThread;
	
//	Entity and object
	public Player player = new Player(this, keyH);
	public SuperObject obj[] = new SuperObject[10];
	public Entity npc[] = new Entity[10];
	
//	GAME STATE
	public int gameState;
	public final int titleState = 0;
	public final int playState = 1;
	public final int pauseState = 2;
	public final int dialogueState = 3;
	
	public GamePanel() {
		this.setPreferredSize(new Dimension(screenWidth, screenHeight));
		this.setBackground(Color.black);
		this.setDoubleBuffered(true);
		this.addKeyListener(keyH);
		this.setFocusable(true);
	}
	
	public void setupGame() {
		aSetter.setObject();
		
		aSetter.setNPC();
		
//		playMusic(0);
		
		gameState = titleState;
		
//		stopMusic();
	}
	
	public void startGameThread() {
		gameThread = new Thread(this);
		gameThread.start();
	}
	
	// @Override
	public void run() {
//		Delta / Accumulator method
		double drawInterval = 1000000000/FPS;
		double delta = 0;
		long lastTime = System.nanoTime();
		long currentTime;
		long timer = 0;
		int drawCount = 0;
		
		while (gameThread != null) {
			currentTime = System.nanoTime();
			
			delta += (currentTime - lastTime) / drawInterval;
			timer += (currentTime - lastTime);
			lastTime = currentTime;
			
			if (delta >= 1) {
				update();
				repaint();
				delta--;
				drawCount++;
			}
			
			if (timer > 1000000000) {
				System.out.println("FPS: " + drawCount);
				drawCount = 0;
				timer = 0;
			}
		}
	}
	
	public void update() {
		if (gameState == playState) {
//			PLAYER
			player.update();
			
//			NPCs
			for (int i = 0; i < npc.length; ++i) {
				if (npc[i] != null) {
					npc[i].update();
				}
			}
		}
		if (gameState == pauseState) {
			
		}
	}
	
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		
		Graphics2D g2 = (Graphics2D)g;
		
//		DEBUG
		long drawStart = 0;
		if (keyH.checkDrawTime == true) {
			drawStart = System.nanoTime();
		}
		
//		TITLE SCREEN
		if (gameState == titleState) {
			ui.draw(g2);
		}
//		OTHERS
		else {
//			TILE
			tileM.draw(g2);
			
//			OBJECT
			for (int i = 0; i < obj.length; ++i) {
				if (obj[i] != null) {
					obj[i].draw(g2, this);
				}
			}
			
//			NPC
			for (int i = 0; i < npc.length; ++i) {
				if (npc[i] != null) {
					npc[i].draw(g2);
				}
			}
			
//			PLAYER
			player.draw(g2);
			
//			UI
			ui.draw(g2);	
		}
		
//		DEBUG
		if (keyH.checkDrawTime == true) {
			long drawEnd = System.nanoTime();
			long passed = drawEnd - drawStart;
			g2.setColor(Color.yellow);
			g2.drawString("Draw time: " + passed, 10, 400);
			System.out.println("Draw time: " + passed);
		}
		
		g2.dispose();
	}
	
	public void playMusic(int i) {
		music.setFile(i);
		music.play();
		music.loop();
	}
	
	public void stopMusic() {
		music.stop();
	}
	
//	Sound Effect
	public void playSE(int i) {
		se.setFile(i);
		se.play();
	}
}
