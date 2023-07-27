import numpy as np
import matplotlib.pyplot as plt
import h5py as h5

if __name__ == "__main__":

    Nr = 256
    Nth = 128

    rmin = 1.0
    rmax = 100
    thmin = 0.0
    thmax = np.pi

    r1 = np.linspace(rmin, rmax, Nr)
    th1 = np.linspace(thmin, thmax, Nth)

    r, th = np.meshgrid(r1, th1)



    Ac_t = np.zeros(r.shape)
    Ac_r = np.zeros(r.shape)
    Ac_th = np.zeros(r.shape)
    Ac_ph = np.exp(-0.5*((r-20)**2 + (r*np.cos(th))**2)/(2.0)**2)
    
    As_t = np.zeros(r.shape)
    As_r = np.zeros(r.shape)
    As_th = np.zeros(r.shape)
    As_ph = -np.exp(-0.5*((r-20)**2 + (r*np.cos(th))**2)/(2.0)**2)

    Ac = np.empty((4, Nth, Nr))
    As = np.empty((4, Nth, Nr))

    Ac[0] = Ac_t
    Ac[1] = Ac_r
    Ac[2] = Ac_th
    Ac[3] = Ac_ph

    As[0] = As_t
    As[1] = As_r
    As[2] = As_th
    As[3] = As_ph

    with h5.File("Amu.h5", "w") as f:
        f.create_dataset("r", data=r1, dtype=float)
        f.create_dataset("th", data=th1, dtype=float)
        f.create_dataset("Ac", data=Ac, dtype=float)
        f.create_dataset("As", data=As, dtype=float)
