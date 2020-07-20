import sys
import numpy as np
import matplotlib.pyplot as plt

def print_stats(img):
    print("min: %.3f" % np.min(img))
    print("max: %.3f" % np.max(img))
    print("median: %.3f" % np.median(img))
    print("mean: %.3f" % np.mean(img))
    print("std: %.3f" % np.std(img))

def main():
    if len(sys.argv) == 3:
        filename = sys.argv[1]
        clip_th = int(sys.argv[2])
    else:
        print("Usage: show filename threshold")
        exit()

    print("loading %s" % filename)
    img = np.loadtxt(filename)
    print("file statistics:")
    print_stats(img)
    print("clipping values abouve %d" % clip_th)
    cimg = np.minimum(img, clip_th)
    diff = img - cimg
    diff_count = np.count_nonzero(diff)
    print("clipped %d pixels (%.3f %%)" % (diff_count, 100.0 * diff_count / diff.size))
    print("revised statistics:")
    print_stats(cimg)
    rimg = np.fliplr(cimg.T) # rotate 90 degrees

    plt.imshow(rimg)
    plt.show()

if __name__ == "__main__":
    main()
