#!/usr/bin/python3

from skimage import io

class BrightnessFilter(object):
    def __init__(self, img, scale):
        self.name = img
        self.img = io.imread(img)
        self.scale = scale
    
    def apply(self):
        for i in range(self.img.shape[0]):
            for j in range(self.img.shape[1]):
                if (self.img[i][j][0] + self.scale) > 255:
                    self.img[i][j][0] = 255
                else:
                    self.img[i][j][0] = self.img[i][j][0] + self.scale
                if (self.img[i][j][1] + self.scale) > 255:
                    self.img[i][j][1] = 255
                else:
                    self.img[i][j][1] = self.img[i][j][1] + self.scale
                if (self.img[i][j][2] + self.scale) > 255:
                    self.img[i][j][2] = 255
                else:
                    self.img[i][j][2] = self.img[i][j][2] + self.scale
    
    def show(self):
        io.imshow(self.img)
        io.show()

    def img_save(self):
        io.imsave(self.name.split('.')[0] + '-brig.png', self.img)
	
    def return_img(self):
        return self.img


thr_filter = BrightnessFilter('girassol.jpg', 120)
thr_filter.apply()
thr_filter.show()