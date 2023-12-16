package main;

import javax.swing.*;

public class Main {
	public static JFrame window;
	
	public static void main(String[] args) {
		window = new JFrame();
		
		window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		window.setResizable(false);
		window.setTitle("PROJECT LTM");
		new Main().setIcon();
		
		GamePanel gamePanel = new GamePanel();
		window.add(gamePanel);
		
		gamePanel.config.loadConfig();
		if (gamePanel.fullScreenOn) {
			window.setUndecorated(true);
		}
		
		// Cause the window to be sized to fit the preferred size and layout of its subcomponents(= GamePanel)
		window.pack();
		
		// Center of the screen
		window.setLocationRelativeTo(null);
		window.setVisible(true);
		
		gamePanel.setupGame();
		gamePanel.startGameThread();
	}
	
	public void setIcon() {
		ImageIcon icon = new ImageIcon(getClass().getClassLoader().getResource("player/boy_down_1.png"));
		window.setIconImage(icon.getImage());
	}
}
