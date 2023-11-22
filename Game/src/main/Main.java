package main;

import javax.swing.*;

public class Main {
	public static void main(String[] args) {
		JFrame window = new JFrame();
		
		window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		window.setResizable(false);
		window.setTitle("Ninja Adventure");
		
		GamePanel gamePanel = new GamePanel();
		window.add(gamePanel);
		
		// Cause the window to be sized to fit the preferred size and layout of its subcomponents(= GamePanel)
		window.pack();
		
		// Center of the screen
		window.setLocationRelativeTo(null);
		window.setVisible(true);
		
		gamePanel.setupGame();
		gamePanel.startGameThread();
	}
}
