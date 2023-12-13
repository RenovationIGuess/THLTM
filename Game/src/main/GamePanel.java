package main;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.GraphicsDevice;
import java.awt.GraphicsEnvironment;
import java.awt.image.BufferedImage;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

import javax.swing.JPanel;

import ai.PathFinder;
import entity.Entity;
import entity.Player;
import object.AssetSetter;
import object.SuperObject;
import tile_interactive.InteractiveTile;
import tiles.TileManager;

public class GamePanel extends JPanel implements Runnable {
	private static final long serialVersionUID = 1L;
	// SCREEN SETTINGS
	// Default size of characters, NPCs, tiles
	final int originalTileSize = 16; // 16x16 tile
	final int scale = 3;
	
	public final int tileSize = originalTileSize * scale; // 48x48 tile
	// Ratio 4:3
	public final int maxScreenCol = 20;
	public final int maxScreenRow = 12;
	public final int screenWidth = tileSize * maxScreenCol;
	public final int screenHeight = tileSize * maxScreenRow;
	
//	For full-screen
	int screenWidth2 = screenWidth;
	int screenHeight2 = screenHeight;
	BufferedImage tempScreen;
	Graphics2D g2;
	public boolean fullScreenOn = false;
	
//	WORLD SETTINGS
	public final int maxWorldCol = 50;
	public final int maxWorldRow = 50;
	public final int maxMap = 10;
	public int currentMap = 0;
	
//	Redundant - can be removed
	public final int worldWidth = tileSize * maxWorldCol;
	public final int worldHeight = tileSize * maxWorldRow;
	
//	FPS
	int FPS = 144;
	
	public TileManager tileM = new TileManager(this);
	public KeyHandler keyH = new KeyHandler(this);
	Sound music = new Sound();
	Sound se = new Sound();
	public CollisionChecker cChecker = new CollisionChecker(this);
	public AssetSetter aSetter = new AssetSetter(this);
	public UI ui = new UI(this);
	public EventHandler eHandler = new EventHandler(this);
	Config config = new Config(this);
	public PathFinder pFinder = new PathFinder(this);
	Thread gameThread;
	
//	Entity and object
	public Player player = new Player(this, keyH);
	public Entity obj[][] = new Entity[maxMap][50];
	public Entity npc[][] = new Entity[maxMap][50];
	public Entity monster[][] = new Entity[maxMap][50];
	public InteractiveTile iTile[][] = new InteractiveTile[maxMap][50];
	ArrayList<Entity> entityList = new ArrayList<>();
	public ArrayList<Entity> particleList = new ArrayList<>();
	public Entity projectile[][] = new Entity[maxMap][20];
	
//	GAME STATE
	public int gameState;
	public final int titleState = 0;
	public final int playState = 1;
	public final int pauseState = 2;
	public final int dialogueState = 3;
	public final int characterState = 4;
	public final int optionsState = 5;
	public final int gameOverState = 6;
	public final int transitionState = 7;
	public final int tradeState = 8;
	
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
		aSetter.setMonster();
		aSetter.setInteractiveTile();
		
//		playMusic(0);
		
		gameState = titleState;
		
		tempScreen = new BufferedImage(screenWidth, screenHeight, BufferedImage.TYPE_INT_ARGB);
		g2 = (Graphics2D)tempScreen.getGraphics();
		
		if (fullScreenOn) {
			setFullScreen();
		}
//		stopMusic();
	}
	
	public void retry() {
		player.setDefaultPositions();
		player.restoreLifeAndMana();
		aSetter.setNPC();
		aSetter.setMonster();
	}
	
	public void restart() {
		player.setDefaultValues();
		player.setItems();
		aSetter.setObject();
		aSetter.setNPC();
		aSetter.setMonster();
		aSetter.setInteractiveTile();
	}
	
	public void setFullScreen() {
//		Get local screen device
		GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
		GraphicsDevice gd = ge.getDefaultScreenDevice();
		
		gd.setFullScreenWindow(Main.window);
		
//		Get full screen w and h
		screenWidth2 = Main.window.getWidth();
		screenHeight2 = Main.window.getHeight();
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
//				repaint();
				drawToTempScreen(); // draw to buffered image
				drawToScreen(); // draw buffered image to screen
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
			for (int i = 0; i < npc[1].length; ++i) {
				if (npc[currentMap][i] != null) {
					npc[currentMap][i].update();
				}
			}
			
//			Monster
			for (int i = 0; i < monster[1].length; ++i) {
				if (monster[currentMap][i] != null) {
					if (monster[currentMap][i].alive == true && monster[currentMap][i].dying == false) {
						monster[currentMap][i].update();
					}
					if (monster[currentMap][i].alive == false) {
						monster[currentMap][i].checkDrop();
						monster[currentMap][i] = null;
					}
				}
			}
			
			for (int i = 0; i < projectile[1].length; ++i) {
				if (projectile[currentMap][i] != null) {
					if (projectile[currentMap][i].alive == true) {
						projectile[currentMap][i].update();
					}
					if (projectile[currentMap][i].alive == false) {
						projectile[currentMap][i] = null;
					}
				}
			}
			
			for (int i = 0; i < particleList.size(); ++i) {
				if (particleList.get(i) != null) {
					if (particleList.get(i).alive == true) {
						particleList.get(i).update();
					}
					if (particleList.get(i).alive == false) {
						particleList.remove(i);
					}
				}
			}
			
			for (int i = 0; i < iTile[1].length; ++i) {
				if (iTile[currentMap][i] != null) {
					iTile[currentMap][i].update();
				}
			}
		}
		if (gameState == pauseState) {
			
		}
	}
	
	public void drawToTempScreen() {
//		DEBUG
		long drawStart = 0;
		if (keyH.showDebugText == true) {
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
			
//			Interactive tile
			for (int i = 0; i < iTile[1].length; ++i) {
				if (iTile[currentMap][i] != null) {
					iTile[currentMap][i].draw(g2);
				}
			}
		
//			ADD ENTITIES TO LIST
			entityList.add(player);
			
			for (int i = 0; i < npc[1].length; ++i) {
				if (npc[currentMap][i] != null) {
					entityList.add(npc[currentMap][i]);
				}
			}
			
			for (int i = 0; i < obj[1].length; ++i) {
				if (obj[currentMap][i] != null) {
					entityList.add(obj[currentMap][i]);
				}
			}
			
			for (int i = 0; i < monster[1].length; ++i) {
				if (monster[currentMap][i] != null) {
					entityList.add(monster[currentMap][i]);
				}
			}
			
			for (int i = 0; i < projectile[1].length; ++i) {
				if (projectile[currentMap][i] != null) {
					entityList.add(projectile[currentMap][i]);
				}
			}
			
			for (int i = 0; i < particleList.size(); ++i) {
				if (particleList.get(i) != null) {
					entityList.add(particleList.get(i));
				}
			}
			
//			Sort
			Collections.sort(entityList, new Comparator<Entity>() {
				@Override
				public int compare(Entity e1, Entity e2) {
					int result = Integer.compare(e1.worldY, e2.worldY);
					return result;
				}
			});
			
//			Draw entities
			for (int i = 0; i < entityList.size(); ++i) {
				entityList.get(i).draw(g2);
			}
			
//			Empty list
			entityList.clear();
			
//			UI
			ui.draw(g2);	
		}
		
//		DEBUG
		if (keyH.showDebugText == true) {
			long drawEnd = System.nanoTime();
			long passed = drawEnd - drawStart;
			g2.setFont(new Font("Arial", Font.PLAIN, 20));
			g2.setColor(Color.white);
			
			int x = 10;
			int y = 400;
			int lineHeight = 24;
			
			g2.drawString("World X: " + player.worldX, x, y);
			y += lineHeight;
			
			g2.drawString("World Y: " + player.worldY, x, y);
			y += lineHeight;
			
			g2.drawString("Col: " + (player.worldX + player.solidArea.x) / tileSize, x, y);
			y += lineHeight;
			
			g2.drawString("Row: " + (player.worldX + player.solidArea.y) / tileSize, x, y);
			y += lineHeight;
			
			g2.drawString("Draw time: " + passed, x, y);
			System.out.println("Draw time: " + passed);
		}
	}
	
//	public void paintComponent(Graphics g) {
//		super.paintComponent(g);
//		
//		Graphics2D g2 = (Graphics2D)g;
//		
////		DEBUG
//		long drawStart = 0;
//		if (keyH.showDebugText == true) {
//			drawStart = System.nanoTime();
//		}
//		
////		TITLE SCREEN
//		if (gameState == titleState) {
//			ui.draw(g2);
//		}
////		OTHERS
//		else {
////			TILE
//			tileM.draw(g2);
//			
////			Interactive tile
//			for (int i = 0; i < iTile.length; ++i) {
//				if (iTile[i] != null) {
//					iTile[i].draw(g2);
//				}
//			}
//		
////			ADD ENTITIES TO LIST
//			entityList.add(player);
//			
//			for (int i = 0; i < npc.length; ++i) {
//				if (npc[i] != null) {
//					entityList.add(npc[i]);
//				}
//			}
//			
//			for (int i = 0; i < obj.length; ++i) {
//				if (obj[i] != null) {
//					entityList.add(obj[i]);
//				}
//			}
//			
//			for (int i = 0; i < monster.length; ++i) {
//				if (monster[i] != null) {
//					entityList.add(monster[i]);
//				}
//			}
//			
//			for (int i = 0; i < projectileList.size(); ++i) {
//				if (projectileList.get(i) != null) {
//					entityList.add(projectileList.get(i));
//				}
//			}
//			
//			for (int i = 0; i < particleList.size(); ++i) {
//				if (particleList.get(i) != null) {
//					entityList.add(particleList.get(i));
//				}
//			}
//			
////			Sort
//			Collections.sort(entityList, new Comparator<Entity>() {
//				@Override
//				public int compare(Entity e1, Entity e2) {
//					int result = Integer.compare(e1.worldY, e2.worldY);
//					return result;
//				}
//			});
//			
////			Draw entities
//			for (int i = 0; i < entityList.size(); ++i) {
//				entityList.get(i).draw(g2);
//			}
//			
////			Empty list
//			entityList.clear();
//			
////			UI
//			ui.draw(g2);	
//		}
//		
////		DEBUG
//		if (keyH.showDebugText == true) {
//			long drawEnd = System.nanoTime();
//			long passed = drawEnd - drawStart;
//			g2.setFont(new Font("Arial", Font.PLAIN, 20));
//			g2.setColor(Color.white);
//			
//			int x = 10;
//			int y = 400;
//			int lineHeight = 24;
//			
//			g2.drawString("World X: " + player.worldX, x, y);
//			y += lineHeight;
//			
//			g2.drawString("World Y: " + player.worldY, x, y);
//			y += lineHeight;
//			
//			g2.drawString("Col: " + (player.worldX + player.solidArea.x) / tileSize, x, y);
//			y += lineHeight;
//			
//			g2.drawString("Row: " + (player.worldX + player.solidArea.y) / tileSize, x, y);
//			y += lineHeight;
//			
//			g2.drawString("Draw time: " + passed, x, y);
//			System.out.println("Draw time: " + passed);
//		}
//		
//		g2.dispose();
//	}
	
	public void drawToScreen() {
		Graphics g = getGraphics();
		g.drawImage(tempScreen, 0, 0, screenWidth2, screenHeight2, null);
		g.dispose();
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
