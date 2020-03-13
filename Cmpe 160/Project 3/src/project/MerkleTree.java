package project;

import java.io.File;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Scanner;
import java.util.Stack;

import util.HashGeneration;

public class MerkleTree {
	public int deep = 0;
	private MyNode root;
	private String path;
	public LinkedList<MyNode> treeNodes;
	public LinkedList<String> treeDatas;

	public MerkleTree(String path) {

		try {

			this.path = path;
			treeNodes = treeCreate(path);
			root = treeNodes.get(0);

			treeDatas = dataLoad();
		} catch (Exception e) {
			// TODO: handle exception
		}

	}

	private LinkedList<String> dataLoad() {
		LinkedList<String> datas = new LinkedList<>();

		for (int i = 0; i < treeNodes.size(); i++) {

			datas.add(treeNodes.get(i).getData());

		}

		return datas;
	}

	public MyNode getRoot() {
		return root;
	}

	public void setRoot(MyNode root) {
		this.root = root;
	}

	private LinkedList<MyNode> treeCreate(String path) {

		LinkedList<MyNode> allNode = new LinkedList<MyNode>();
		try {

			LinkedList<MyNode> list = new LinkedList<MyNode>();

			File file = new File(path);

			Scanner scan = new Scanner(file);

			String link = "";
			String hashOfLink = "";

			while (scan.hasNextLine()) {

				link = scan.nextLine();
				File newPath = new File(link);
				hashOfLink = HashGeneration.generateSHA256(newPath);

				MyNode Node = new MyNode(hashOfLink);
				list.add(Node);
				allNode.add(Node);
				deep++;

			}

			LinkedList<MyNode> temp = new LinkedList<MyNode>();

			while (list.size() > 1) {
				int t = 0;
				String data1 = "";
				String data2 = "";
				String key = "";
				for (int i = 0; i < list.size();) {

					data1 = list.get(i).getData();
					if ((i + 1) < list.size()) {

						data2 = list.get(i + 1).getData();
						key = data1 + data2;
						String newData = HashGeneration.generateSHA256(key);
						MyNode newNode = new MyNode(newData);
						newNode.setLeft(list.get(i));
						newNode.setRight(list.get(i + 1));
						temp.add(newNode);
						allNode.add(t, newNode);

					}

					else {
						data2 = "";
						key = data1 + data2;
						String newData = HashGeneration.generateSHA256(key);
						MyNode newNode = new MyNode(newData);
						newNode.setLeft(list.get(i));
						newNode.setRight(null);
						temp.add(newNode);
						allNode.add(t, newNode);

					}

					i += 2;
					t++;

				}

				list.clear();

				for (int i = 0; i < temp.size(); i++) {

					list.add(temp.get(i));
				}

				temp.clear();

			}
		} catch (Exception e) {
			// TODO: handle exception
		}

		return allNode;

	}

	public LinkedList<Integer> deepList() {

		LinkedList<Integer> deeps = new LinkedList<>();
		int adding = treeNodes.size() - 1;

		for (int i = 0; i < deep; i++) {

			deeps.addFirst(adding - i);
		}

		return deeps;
	}

	public boolean checkAuthenticity(String path) {

		try {
			File file = new File(path);
			Scanner scan = new Scanner(file);

			String check = "";
			int i = 0;
			while (scan.hasNextLine() && treeNodes.size() > i) {

				check = scan.nextLine();

				String data = treeNodes.get(i).getData();

				if (!data.equals(check)) {
					return false;
				}

				if (!scan.hasNextLine() && i > treeNodes.size()) {
					break;
				}

				i++;

			}
		} catch (Exception e) {
			// TODO: handle exception
		}

		return true;

	}

	public ArrayList<Stack<String>> findCorruptChunks(String path) {

		ArrayList<Stack<String>> corrupt = new ArrayList<>();
		try {

			ArrayList<Integer> indexCorr = new ArrayList<>();

			if (!checkAuthenticity(path)) {

				File file = new File(path);
				Scanner scan = new Scanner(file);

				String check = "";
				int i = 0;
				while (scan.hasNextLine() && i < treeNodes.size()) {

					check = scan.nextLine();

					String data = treeNodes.get(i).getData();

					if (!data.equals(check)) {

						indexCorr.add(i);

					}

					if (!scan.hasNextLine() || treeNodes.get(i) == null) {
						break;
					}

					i++;

				}

				corrupt = findCorrupt(indexCorr);
			}
		}

		catch (Exception e) {
			// TODO: handle exception
		}
		return corrupt;

		

	}

	public ArrayList<Stack<String>> findCorrupt(ArrayList<Integer> indexCorr) {

		ArrayList<Stack<String>> corrupt = new ArrayList<>();
		try {
			LinkedList<Integer> numbers = deepList();
			ArrayList<Integer> deepCorr = new ArrayList<>();
			int count = 0;

			for (int i = 0; i < indexCorr.size(); i++) {

				if (numbers.contains(indexCorr.get(i))) {

					deepCorr.add(indexCorr.get(i));
					count++;
				}
			}

			int height = treeNodes.get(0).getHeight() + 1;

			int temp[][] = new int[count][height];

			for (int i = 0; i < count; i++) {
				temp[i][0] = deepCorr.get(i);
			}

			for (int i = 0; i < height - 1; i++) {

				for (int j = 0; j < count; j++) {

					for (int k = 0; k < indexCorr.size(); k++) {
						String add1 = "";
						String add2 = "";

						if (treeNodes.get(indexCorr.get(k)).getLeft() != null) {

							add1 = treeNodes.get(indexCorr.get(k)).getLeft().getData();
						}

						if (treeNodes.get(indexCorr.get(k)).getRight() != null) {

							add2 = treeNodes.get(indexCorr.get(k)).getRight().getData();

						}

						String corr = treeNodes.get(temp[j][i]).getData();

						if (add1.equals(corr)) {

							temp[j][i + 1] = indexCorr.get(k);
						}

						if (add2.equals(corr)) {

							temp[j][i + 1] = indexCorr.get(k);
						}

					}
				}
			}

			for (int i = 0; i < count; i++) {
				Stack<String> stack1 = new Stack<>();
				Stack<String> stack2 = new Stack<>();
				for (int j = 0; j < height; j++) {

					int a = temp[i][j];
					String item = treeNodes.get(a).getData();
					stack1.push(item);

				}

				while (!stack1.isEmpty()) {
					stack2.push(stack1.pop());
				}

				corrupt.add(stack2);
			}
		}
		catch (Exception e) {
			// TODO: handle exception
		}

		return corrupt;
	}

}
