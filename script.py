import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
import scipy.integrate as ODE
import argparse


def solve_ivp_sencillo(ecuacion, Xo, tini, tfin, ciclos, parametros=[], plot=True):
    t = np.linspace(tini, tfin, ciclos)
    dxdt = np.zeros(len(ecuacion))

    def modelo(t, x):
        p = parametros
        for n, e in enumerate(ecuacion):
            dxdt[n] = eval(e)
        return dxdt

    r = ODE.solve_ivp(modelo, (tini, tfin), Xo, 'RK45', t_eval=t)
   # print(r.sol)
    if plot:
        plt.figure(1)
        for n in range(len(ecuacion)):
            plt.plot(r.t, r.y[n])
        if len(ecuacion) == 2 or len(ecuacion) == 3:
            plt.figure(2)
            if len(ecuacion) == 2:
                plt.plot(r.y[0], r.y[1], linewidth=.8)
            elif len(ecuacion) == 3:
                ax = plt.axes(projection='3d')
                ax.plot3D(r.y[0], r.y[1], r.y[2], linewidth=.8)
        plt.show()

    return r


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Ejecutar solve_ivp_sencillo con argumentos')
    parser.add_argument('--ecuacion', type=str, help='Lista de ecuaciones')
    parser.add_argument('--Xo', type=str, help='Valores iniciales')
    parser.add_argument('--tini', type=float, help='Tiempo inicial')
    parser.add_argument('--tfin', type=float, help='Tiempo final')
    parser.add_argument('--ciclos', type=int, help='Número de ciclos')
    args = parser.parse_args()
    ecuaciones = args.ecuacion.split()

    # Convertir la cadena de valores Xo en una lista de valores flotantes
    Xo_values = list(map(float, args.Xo.split()))

    print("Expresiones de ecuacion:", ecuaciones)

    solve_ivp_sencillo(ecuaciones, Xo_values, args.tini, args.tfin, args.ciclos)


