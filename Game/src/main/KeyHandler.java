package main;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class KeyHandler implements KeyListener {
	public boolean upPressed, downPressed, leftPressed, rightPressed, enterPressed, shotKeyPressed;
	GamePanel gp;
	
//	DEBUG
	boolean showDebugText = false;
	
	public KeyHandler(GamePanel gp) {
		this.gp = gp;
	}
	
	public void keyTyped(KeyEvent e) {
		// TODO Auto-generated method stub
		
	}

	public void keyPressed(KeyEvent e) {
		// TODO Auto-generated method stub
		int code = e.getKeyCode();
		
//		System.out.println("Key code: " + code);
		
//		TITLE STATE
		if (gp.gameState == gp.titleState) {
			titleState(code);
		}
		
//		Play state
		else if (gp.gameState == gp.playState) {
			playState(code);
		}
		
//		PAUSE STATE
		else if (gp.gameState == gp.pauseState) {
			pauseState(code);
		}
		
		else if (gp.gameState == gp.dialogueState) {
			dialogueState(code);
		}
		
//		Character state
		else if (gp.gameState == gp.characterState) {
			characterState(code);
		}
		
		else if (gp.gameState == gp.optionsState) {
			optionsState(code);
		}
		
		else if (gp.gameState == gp.gameOverState) {
			gameOverState(code);
		}
	}
	
	public void titleState(int code) {
		if (gp.ui.titleScreenState == 0) {
			if (code == KeyEvent.VK_W) {
				if (gp.ui.commandNum == 0) {
					gp.ui.commandNum = 2;
				} else gp.ui.commandNum--;
			}
			
			if (code == KeyEvent.VK_S) {
				if (gp.ui.commandNum == 2) {
					gp.ui.commandNum = 0;
				} else gp.ui.commandNum++;
			}
			
			if (code == KeyEvent.VK_ENTER) {
				if (gp.ui.commandNum == 0) {
					gp.gameState = gp.playState;
					gp.playMusic(21);
//					gp.ui.titleScreenState = 1;
				}
				
				if (gp.ui.commandNum == 1) {
//					
				}
				
				if (gp.ui.commandNum == 2) {
					System.exit(0);
				}
			}
		}
		
		else if (gp.ui.titleScreenState == 1) {
			if (code == KeyEvent.VK_W) {
				if (gp.ui.commandNum == 0) {
					gp.ui.commandNum = 3;
				} else gp.ui.commandNum--;
			}
			
			if (code == KeyEvent.VK_S) {
				if (gp.ui.commandNum == 3) {
					gp.ui.commandNum = 0;
				} else gp.ui.commandNum++;
			}
			
			if (code == KeyEvent.VK_ENTER) {
				if (gp.ui.commandNum == 0) {
//					TODO: Fighter class chosen
					gp.gameState = gp.playState;
//					gp.playMusic(0);
					gp.ui.titleScreenState = 1;
				}
				
				if (gp.ui.commandNum == 1) {
//					TODO: Thief class chosen
					gp.gameState = gp.playState;
//					gp.playMusic(0);
				}
				
				if (gp.ui.commandNum == 2) {
//					TODO: Sorcerer class chosen
					gp.gameState = gp.playState;
//					gp.playMusic(0);
				}
				
				if (gp.ui.commandNum == 3) {
					gp.ui.titleScreenState = 0;
					gp.ui.commandNum = 0;
				}
			}
		}
	}
	
	public void playState(int code) {
		if (code == KeyEvent.VK_W) {
			upPressed = true;
		}
		
		if (code == KeyEvent.VK_S) {
			downPressed = true;
		}

		if (code == KeyEvent.VK_A) {
			leftPressed = true;
		}

		if (code == KeyEvent.VK_D) {
			rightPressed = true;
		}
		
		if (code == KeyEvent.VK_P) {
			gp.gameState = gp.pauseState;
		}
		
		if (code == KeyEvent.VK_ENTER) {
			enterPressed = true;
		}
		
		if (code == KeyEvent.VK_C) {
			gp.gameState = gp.characterState;
		}
		
		if (code == KeyEvent.VK_F) {
			shotKeyPressed = true;
		}
		
		if (code == KeyEvent.VK_ESCAPE) {
			gp.gameState = gp.optionsState;
		}
		
//		DEBUG
		if (code == KeyEvent.VK_T) {
			if (!showDebugText) {
				showDebugText = true;
			} else showDebugText = false;
		}
		
		if (code == KeyEvent.VK_R) {
			gp.tileM.loadMap("/map/worldV2.txt");
		}
	}
	
	public void pauseState(int code) {
		if (code == KeyEvent.VK_P) {
//			System.out.println("P key pressed.");
			gp.gameState = gp.playState;
		}
	}
	
	public void dialogueState(int code) {
		if (code == KeyEvent.VK_ENTER) {
//			System.out.println("Enter key pressed.");
			gp.gameState = gp.playState;
		}
	}
	
	public void characterState(int code) {
		if (code == KeyEvent.VK_C) {
			gp.gameState = gp.playState;
		}
		if (code == KeyEvent.VK_W) {
			if (gp.ui.slotRow != 0) {
				gp.ui.slotRow--;
				gp.playSE(9);
			}
		}
		
		if (code == KeyEvent.VK_A) {
			if (gp.ui.slotCol != 0) {
				gp.ui.slotCol--;
				gp.playSE(9);
			}
		}
		
		if (code == KeyEvent.VK_S) {
			if (gp.ui.slotRow != 3) {
				gp.ui.slotRow++;
				gp.playSE(9);
			}
		}
		
		if (code == KeyEvent.VK_D) {
			if (gp.ui.slotCol != 4) {
				gp.ui.slotCol++;
				gp.playSE(9);
			}
		}
		
		if (code == KeyEvent.VK_ENTER) {
			gp.player.selectItem();
		}
	}
	
	public void optionsState(int code) {
		if (code == KeyEvent.VK_ESCAPE) {
			gp.gameState = gp.playState;
		}
		
		if (code == KeyEvent.VK_ENTER) {
			enterPressed = true;
		}
		
		int maxCommandNum = 0;
		switch (gp.ui.subState) {
		case 0: maxCommandNum = 5; break;
		case 3: maxCommandNum = 1; break;
		}
		
		if (code == KeyEvent.VK_W) {
			gp.ui.commandNum--;
			gp.playSE(9);
			
			if (gp.ui.commandNum < 0) {
				gp.ui.commandNum = maxCommandNum;
			}
		}
		
		if (code == KeyEvent.VK_S) {
			gp.ui.commandNum++;
			gp.playSE(9);
			
			if (gp.ui.commandNum > maxCommandNum) {
				gp.ui.commandNum = 0;
			}
		}
		
		if (code == KeyEvent.VK_A) {
			if (gp.ui.subState == 0) {
				if (gp.ui.commandNum == 1 && gp.music.volumeScale > 0) {
					gp.music.volumeScale--;
					gp.music.checkVolume();
					gp.playSE(9);
				}
				if (gp.ui.commandNum == 2 && gp.se.volumeScale > 0) {
					gp.se.volumeScale--;
					gp.playSE(9);
				}
			}
		}
		
		if (code == KeyEvent.VK_D) {
			if (gp.ui.subState == 0) {
				if (gp.ui.commandNum == 1 && gp.music.volumeScale < 5) {
					gp.music.volumeScale++;
					gp.music.checkVolume();
					gp.playSE(9);
				}
				if (gp.ui.commandNum == 2 && gp.se.volumeScale < 5) {
					gp.se.volumeScale++;
					gp.playSE(9);
				}
			}
		}
	}
	
	public void gameOverState(int code) {
		if (code == KeyEvent.VK_W) {
			gp.ui.commandNum--;
			if (gp.ui.commandNum < 0) {
				gp.ui.commandNum = 1;
			}
			gp.playSE(9);
		}
		
		if (code == KeyEvent.VK_S) {
			gp.ui.commandNum++;
			if (gp.ui.commandNum > 1) {
				gp.ui.commandNum = 0;
			}
			gp.playSE(9);
		}
		
		if (code == KeyEvent.VK_ENTER) {
			if (gp.ui.commandNum == 0) {
				gp.retry();
				gp.gameState = gp.playState;
				gp.playMusic(21);
			} 
			else if (gp.ui.commandNum == 1) {
				gp.gameState = gp.titleState;
				gp.restart();
			}
		}
	}

	public void keyReleased(KeyEvent e) {
		// TODO Auto-generated method stub
		int code = e.getKeyCode();
		
		if (code == KeyEvent.VK_W) {
			upPressed = false;
		}
		
		if (code == KeyEvent.VK_S) {
			downPressed = false;
		}

		if (code == KeyEvent.VK_A) {
			leftPressed = false;
		}

		if (code == KeyEvent.VK_D) {
			rightPressed = false;
		}
		
		if (code == KeyEvent.VK_F) {
			shotKeyPressed = false;
		}
	}
}
