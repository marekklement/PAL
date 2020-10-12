package pal;

public class Node implements Comparable<Node> {

    int weight;
    int index;
    int level;

    public Node(int weight, int index) {
        this.weight = weight;
        this.index = index;
    }

    public int compareTo(Node e) {
        return weight - e.weight;
    }
}

