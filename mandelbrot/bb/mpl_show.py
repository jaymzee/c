import sys
import os
import numpy as np
import matplotlib.pyplot as plt

def print_stats(arr, header):
    if msg:
        print(header)
        indent = "    "
    else:
        indent = ""
    print("%smin: %.3f, max: %.3f" % (indent, np.min(arr), np.max(arr)))
    print("%smedian: %.3f, mean: %.3f, std: %.3f" % (indent, np.median(arr), np.mean(arr), np.std(arr)))


def main():
    # process command line arguments
    if len(sys.argv) == 3:
        in_filename = sys.argv[1]
        clip_th = int(sys.argv[2])
    else:
        print("Usage: mpl_show filename threshold")
        exit(1)

    # read rendered image into numpy array
    print("reading %s" % in_filename)
    init_arr = np.loadtxt(in_filename)
    print_stats(init_arr, "input file statistics:")

    # clip values
    print("clipping values abouve %d" % clip_th)
    clipped_arr = np.minimum(init_arr, clip_th)
    diff_arr = init_arr - clipped_arr
    diff_count = np.count_nonzero(diff_arr)
    print("clipped %d pixels (%.3f %%)" % (diff_count, 100.0 * diff_count / diff_arr.size))
    print_stats(clipped_arr, "statistics after clipping:")

    # rotate image right 90 degrees
    rot_arr = np.fliplr(clipped_arr.T) # rotate 90 degrees

    # display image momentarily
    plt.imshow(rot_arr)
    plt.show()

    # write PNG image
    out_basename, ext = os.path.splitext(in_filename)
    out_filename = out_basename + ".png"
    print("writing PNG image to %s" % out_filename)
    plt.imsave(out_filename, rot_arr)


if __name__ == "__main__":
    main()
