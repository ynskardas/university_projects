package project;

public class MyNode {

	private String data;
	private MyNode left = null;
	private MyNode right = null;

	public MyNode(String data) {
		this.data = data;
	}

	public String getData() {
		return data;
	}

	public void setData(String data) {
		this.data = data;
	}

	public MyNode getLeft() {
		return left;
	}

	public void setLeft(MyNode left) {
		this.left = left;
	}

	public MyNode getRight() {
		return right;
	}

	public void setRight(MyNode right) {
		this.right = right;
	}

	public String toString() {
		return String.valueOf(data);
	}

	public int getHeight() {
		int lH = -1;
		int rH = -1;

		if (left != null) {
			lH = left.getHeight();
		}
		if (right != null) {
			rH = right.getHeight();
		}
		return Math.max(rH, lH) + 1;
	}

}
