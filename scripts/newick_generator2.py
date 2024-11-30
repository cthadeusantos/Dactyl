import random
import string
import argparse


class NewickTreeGenerator:
    def __init__(self, num_trees, num_leaves, max_height, rooted=True, use_letters=False, level_leaves=False):
        self.num_trees = num_trees
        self.num_leaves = num_leaves
        self.max_height = max_height
        self.rooted = rooted
        self.use_letters = use_letters
        self.level_leaves = level_leaves

    def generate_label(self, index):
        """Generate a label using numbers or letters."""
        if self.use_letters:
            letters = string.ascii_uppercase
            label = ""
            while index >= 0:
                label = letters[index % 26] + label
                index = index // 26 - 1
            return label
        else:
            return str(index + 1)

    def generate_random_tree(self, labels, current_height=1):
        """Recursively generate a random tree in Newick format."""
        if len(labels) == 1 or (self.level_leaves and current_height == self.max_height):
            # Base case: a single leaf or forced level-leaf condition
            return labels[0]

        # Split labels into random groups ensuring all labels are used
        num_children = random.randint(2, min(len(labels), self.num_leaves))
        children_sizes = [len(labels) // num_children + (1 if x < len(labels) % num_children else 0) for x in range(num_children)]

        subtrees = []
        start = 0
        for size in children_sizes:
            group = labels[start:start + size]
            subtree = self.generate_random_tree(group, current_height + 1)
            subtrees.append(subtree)
            start += size

        return "(" + ",".join(subtrees) + ")"

    def generate_trees(self):
        """Generate N trees as specified."""
        trees = []
        for _ in range(self.num_trees):
            labels = [self.generate_label(i) for i in range(self.num_leaves)]
            random.shuffle(labels)
            tree = self.generate_random_tree(labels)
            if self.rooted:
                tree = f"({tree})"
            tree += ";"
            trees.append(tree)
        return trees

    def save_trees(self):
        """Save trees to individual files."""
        trees = self.generate_trees()
        for i, tree in enumerate(trees, 1):
            filename = f"Tree-{self.num_leaves}l-{i}.arv"
            with open(filename, "w") as f:
                f.write(tree)
            print(f"Tree saved to {filename}")


def main():
    parser = argparse.ArgumentParser(description="Generate random trees in Newick format.")
    parser.add_argument("-t",  type=int, required=True, help="Number of trees to generate.")
    parser.add_argument("-l",  type=int, required=True, help="Number of leaves in the tree.")
    parser.add_argument("-H",  type=int, required=True, help="Maximum height of the tree.")
    parser.add_argument("-r",  action="store_true", help="Generate rooted trees (default).")
    parser.add_argument("-A", action="store_true", help="Use letters for leaf labels instead of numbers.")
    parser.add_argument("--level", action="store_true", help="Ensure all leaves are at the same level.")

    args = parser.parse_args()

    generator = NewickTreeGenerator(
        num_trees=args.t,
        num_leaves=args.l,
        max_height=args.H,
        rooted=args.r,
        use_letters=args.A,
        level_leaves=args.level
    )
    generator.save_trees()


if __name__ == "__main__":
    main()