package main;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class Config {
	GamePanel gp;
	
	public Config(GamePanel gp) {
		this.gp = gp;
	}
	
	public void saveConfig() {
		try {
			BufferedWriter bw = new BufferedWriter(new FileWriter("config"));
			
//			Full screen
			if (gp.fullScreenOn) {
				bw.write("On");
			}
			if (!gp.fullScreenOn) {
				bw.write("Off");
			}
			bw.newLine();
			
//			Music volume
			bw.write(String.valueOf(gp.music.volumeScale));
			bw.newLine();
			
//			SE volume
			bw.write(String.valueOf(gp.se.volumeScale));
			bw.newLine();
			
			bw.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void loadConfig() {
		try {
			BufferedReader br = new BufferedReader(new FileReader("config"));
			
			String s = br.readLine();
			
//			Full screen
			if (s.equals("On")) {
				gp.fullScreenOn = true;
			} else {
				gp.fullScreenOn = false;
			}
			
//			Music volume
			s = br.readLine();
			gp.music.volumeScale = Integer.parseInt(s);
			
//			SE volume
			s = br.readLine();
			gp.se.volumeScale = Integer.parseInt(s);
			
			br.close();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
