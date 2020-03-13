package main;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.net.MalformedURLException;
import java.net.URL;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Scanner;
import java.util.Stack;

import project.MerkleTree;
import util.HashGeneration;

public class Main {

	public static void main(String[] args) {

		

			MerkleTree m0 = new MerkleTree("sample/white_walker.txt");

			String hash = m0.getRoot().getLeft().getRight().getData();
			System.out.println(hash);

			boolean valid = m0.checkAuthenticity("sample/white_walkermeta.txt");
			System.out.println(valid);

			// The following just is an example for you to see the usage.
			// Although there is none in reality, assume that there are two corrupt chunks
			// in this example.
			ArrayList<Stack<String>> corrupts = m0.findCorruptChunks("sample/white_walkermeta.txt");

			System.out.println("Corrupt hash of first corrupt chunk is: " + corrupts.get(0).pop());
			System.out.println("Corrupt hash of second corrupt chunk is: " + corrupts.get(1).pop());
			
			download("secondaryPart/data/download_from_trusted.txt");
			

		

	}

	public static void download(String path) {
		// Entry point for the secondary part

		try {
			LinkedList<MerkleTree> html = new LinkedList<>();

			File file = new File(path);
			Scanner scan = new Scanner(file);

			LinkedList<String> meta = new LinkedList<>();
			LinkedList<String> url1 = new LinkedList<>();
			LinkedList<String> urlAlt = new LinkedList<>();

			String link = "";

			while (scan.hasNextLine()) {

				link = scan.nextLine();

				if (link.contains("meta")) {
					meta.add(link);
				}

				else if (link.contains("alt")) {
					urlAlt.add(link);
				}

				else if (link.contains("txt")) {
					url1.add(link);
				}

			}

			LinkedList<String> path2 = new LinkedList<>();
			LinkedList<String> path2Alt = new LinkedList<>();
			LinkedList<String> path2Meta = new LinkedList<>();

			for (int k = 0; k < 3; k++) {
				LinkedList<String> variable = new LinkedList<>();

				if (k == 0) {
					variable = meta;
				}

				if (k == 1) {
					variable = url1;
				}

				if (k == 2) {
					variable = urlAlt;
				}

				for (int i = 0; i < variable.size(); i++) {

					String fileName = "";

					int size = variable.get(i).length();
					int loca = 0;

					for (int j = 0; j < size; j++) {

						if (variable.get(i).charAt(j) == '/') {
							loca = j;
						}
					}

					fileName = variable.get(i).substring(loca + 1, size);

					fileName = "secondaryPart/data/" + fileName;
					if (k == 0) {
						path2Meta.add(fileName);
					}
					if (k == 1) {
						path2.add(fileName);
					}
					if (k == 2) {
						path2Alt.add(fileName);
					}

					File newFile = new File(fileName);
					if (!newFile.exists()) {
						newFile.createNewFile();
					}

					BufferedWriter temp = new BufferedWriter(new FileWriter(newFile));

					URL x = new URL(variable.get(i));
					BufferedReader in = new BufferedReader(new InputStreamReader(x.openStream()));

					String input;
					String inputLine = "";
					while ((input = in.readLine()) != null) {

						inputLine += input + "\n";
					}
					temp.write(inputLine);
					temp.close();

				}

			}

			for (int j = 0; j < 2; j++) {

				LinkedList<String> path2x = new LinkedList<>();

				if (j == 0) {
					path2x = path2;
				}

				if (j == 1) {

					path2x = path2Alt;
				}

				for (int i = 0; i < path2x.size(); i++) {

					boolean test = true;

					String general1 = "";
					String general2 = "";

					File newRead = new File(path2x.get(i));
					Scanner reader = new Scanner(newRead);
					while (reader.hasNextLine()) {

						String read = reader.nextLine();
						int size = read.length();

						int loca1 = 0;
						int loca2 = 0;
						for (int k = 0; k < size; k++) {

							if (read.charAt(k) == '/') {
								loca1 = k;
							}
						}

						for (int k = 0; k < loca1; k++) {

							if (read.charAt(k) == '/') {
								loca2 = k;
							}
						}
						String pathRead1 = read.substring(loca2 + 1, loca1);
						String pathRead2 = read.substring(loca1 + 1, size);
						String fileName = "";
						if (j == 0) {
							fileName = "secondaryPart/data/split/" + pathRead1;

						} else {
							fileName = "secondaryPart/data/split/" + "Alt" + pathRead1;

						}

						if (test) {
							File newFile = new File(fileName);
							newFile.mkdirs();
							if (newFile.exists()) {
								newFile.createNewFile();
							}

							test = false;
						}

						String nameFile = fileName + "/" + pathRead2;

						if (j == 0) {
							general1 += nameFile + "\n";
						} else {
							general2 += nameFile + "\n";
						}

						File newFile2 = new File(nameFile);

						if (newFile2.exists()) {
							newFile2.createNewFile();
						}

						URL url = new URL(read);
						BufferedInputStream bis = new BufferedInputStream(url.openStream());
						FileOutputStream fis = new FileOutputStream(newFile2);
						byte[] buffer = new byte[1024];
						int count = 0;
						while ((count = bis.read(buffer, 0, 1024)) != -1) {
							fis.write(buffer, 0, count);
						}
						fis.close();
						bis.close();

					}

					if (j == 0) {
						BufferedWriter temp = new BufferedWriter(new FileWriter(path2.get(i)));
						temp.write(general1);
						temp.close();
					} else {
						BufferedWriter temp = new BufferedWriter(new FileWriter(path2Alt.get(i)));
						temp.write(general2);
						temp.close();
					}

				}
			}

			for (int i = 0; i < path2.size(); i++) {

				MerkleTree m1 = new MerkleTree(path2.get(i));
				
				while (!m1.checkAuthenticity(path2Meta.get(i))) {
					
					LinkedList<String> pick2 = new LinkedList<>();
					LinkedList<String> pick2Meta = new LinkedList<>();
					LinkedList<String> pick2Alt = new LinkedList<>();
					LinkedList<String> pickTrue = new LinkedList<>();

					File file2 = new File(path2.get(i));
					Scanner scan2 = new Scanner(file2);

					while (scan2.hasNextLine()) {
						pick2.add(scan2.nextLine());
					}

					File file2Meta = new File(path2Meta.get(i));
					Scanner scan2Meta = new Scanner(file2Meta);

					while (scan2Meta.hasNextLine()) {
						pick2Meta.add(scan2Meta.nextLine());
					}

					File file2Alt = new File(path2Alt.get(i));
					Scanner scan2Alt = new Scanner(file2Alt);

					while (scan2Alt.hasNextLine()) {
						pick2Alt.add(scan2Alt.nextLine());
					}
					int size = pick2Meta.size();
					int number = m1.deep;
					int k = 0;
					for (int j = size - number; j < size; j++) {

						if (m1.treeNodes.get(j).getData().equals(pick2Meta.get(j))) {

							pickTrue.add(pick2.get(k));
						} else {
							pickTrue.add(pick2Alt.get(k));
						}
						k++;
					}

					String writer = "";

					for (int j = 0; j < pickTrue.size(); j++) {

						writer += pickTrue.get(j) + "\n";
					}

					BufferedWriter temp = new BufferedWriter(new FileWriter(path2.get(i)));
					temp.write(writer);
					temp.close();

					m1 = new MerkleTree(path2.get(i));

				}
				
			}

		} catch (Exception e) {
			// TODO: handle exception
		}

	}

}
