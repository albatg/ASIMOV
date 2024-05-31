import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
import scipy.integrate as ODE
import argparse


def solve_ivp_sencillo(ecuaciones, Xo, tini, tfin, ciclos, parametros=[], plot=True):
    t = np.linspace(tini, tfin, ciclos)

    # Definición del modelo
    def modelo(t, x):
        # Las ecuaciones deben pasar como cadena para usar eval
        dxdt = np.zeros_like(x)  # Usar 'zeros_like(x)' para asegurarse de que dxdt tenga la misma forma que x
        p = parametros
        # Utilizar x directamente para referirse a las componentes de estado
        locals_dict = {'x': x, 'p': p, 't': t, 'np': np}
        for n, e in enumerate(ecuaciones):
            try:
                dxdt[n] = eval(e, {"__builtins__": None}, locals_dict)
            except Exception as ex:
                print(f"Error al evaluar la ecuación {n}: {e}")
                print(f"Variables locales: {locals_dict}")
                raise ex
        return dxdt

    # Resolver el sistema de ecuaciones diferenciales
    r = ODE.solve_ivp(modelo, (tini, tfin), Xo, method='Radau', t_eval=t)

    # Generar gráficos si es necesario
    if plot:
        labels = [
           'ADP', 'ATP', 'ADP', 'Fru6P', 'Fru16BP', 'DHAP',
           'GAP', 'BPG', 'NADH', '3PG', '2PG', 'PEP', 'Pyr'
       ]
        plt.figure(1)
        for n in range(len(ecuaciones)):
            plt.plot(r.t, r.y[n], label=labels[n])
            plt.legend(loc='upper left', fontsize='small', bbox_to_anchor=(1, 1))
        if len(ecuaciones) == 2 or len(ecuaciones) >= 3:
            plt.figure(2)
            if len(ecuaciones) == 2:
                plt.plot(r.y[0], r.y[1], linewidth=0.8)
            elif len(ecuaciones) >= 3:
                ax = plt.axes(projection='3d')
                ax.plot3D(r.y[0], r.y[1], r.y[2], linewidth=0.8)
        plt.show()
        print(r)
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

"""
    ecuaciones = [
    "(-p[0]*x[0]*x[1]/(x[0]*x[1]+p[2]*x[0]+p[1]*p[2]))",  # ADP
    "(-p[0]*x[0]*x[1]/(x[0]*x[1]+p[2]*x[0]+p[1]*p[2]))+(p[15]*x[6]*x[8]/(x[6]*x[8]+p[17]*x[6]+p[16]*p[17]))+(p[27]*x[11]*x[2]/(x[11]*x[2]+p[29]*x[11]+p[28]*p[29]))",  # ATP
    "(p[0]*x[0]*x[1]/(x[0]*x[1]+p[2]*x[0]+p[1]*p[2]))-(p[15]*x[6]*x[8]/(x[6]*x[8]+p[17]*x[6]+p[16]*p[17]))-(p[27]*x[11]*x[2]/(x[11]*x[2]+p[29]*x[11]+p[28]*p[29]))",  # ADP
    "(p[0]*x[0]*x[1])/(x[0]*x[1]+p[2]*x[0]+p[1]*p[2]) - ((p[3]*x[3]/p[4]) - (p[6]*x[4]/p[7])) / (1 + x[3]/p[4] + x[4]/p[7])",  # Fru6p
    "(p[3]*x[3]/p[4]) / (1 + x[3]/p[4] + x[4]/p[7]) - (p[6]*x[4]/p[7]) / (1 + x[3]/p[4] + x[4]/p[7])",  # Fru16BP
    "(p[9]*x[4]*x[5]) / (x[4]*x[5] + p[11]*x[4] + p[10]*p[11])",  # DHAP
    "(p[9]*x[4]*x[5]) / (x[4]*x[5] + p[11]*x[4] + p[10]*p[11]) - (p[12]*x[5]*x[6]) / (x[5]*x[6] + p[14]*x[5] + p[13]*p[14])",  # GAP
    "(p[12]*x[5]*x[6]) / (x[5]*x[6] + p[14]*x[5] + p[13]*p[14]) - (p[15]*x[2]*x[7]) / (x[2]*x[7] + p[20]*x[2] + p[19]*p[20])",  # BPG
    "(p[15]*x[2]*x[7]) / (x[2]*x[7] + p[20]*x[2] + p[19]*p[20])",  # NADH
    #"(p[15]*x[6]*x[8] / (x[6]*x[8] + p[17]*x[6] + p[16]*p[17])) - (p[18]*x[2]*x[7] / (x[2]*x[7] + p[20]*x[2] + p[19]*p[20]))",  # ADP
    "(p[18]*x[2]*x[7] / (x[2]*x[7] + p[20]*x[2] + p[19]*p[20])) - p[21]*x[7]*x[9] / (x[7]*x[9] + p[23]*x[7] + p[22]*p[23])",  # 3PG
    "(p[21]*x[7]*x[9] / (x[7]*x[9] + p[23]*x[7] + p[22]*p[23]))",  # 2PG
    "(p[21]*x[7]*x[9] / (x[7]*x[9] + p[23]*x[7] + p[22]*p[23])) - p[24]*x[9]*x[11] / (x[9]*x[11] + p[26]*x[9] + p[25]*p[26])",  # PEP
    "(p[24]*x[9]*x[11] / (x[9]*x[11] + p[26]*x[9] + p[25]*p[26])) - p[27]*x[11]*x[2] / (x[11]*x[2] + p[29]*x[11] + p[28]*p[29])",  # Pyr
    #"(p[27]*x[11]*x[2] / (x[11]*x[2] + p[29]*x[11] + p[28]*p[29]))"  # ATP

    ]

# Llamada a la función
solve_ivp_sencillo(ecuaciones, [0.042,0.0028,0.042,0.0028,0.042,0.0028,0.042,0.0028,0.0028,0.042,0.042,0.0028,0.042], 0, 10, 10000, [10, 2.5e-5, 2.5e-5, 12, 2.5e-5, 2.5e-5, 15, 2.5e-5, 2.5e-5, 20, 2.5e-5, 2.5e-5, 20, 2.5e-5, 2.5e-5, 20, 2.5e-5, 2.5e-5, 20, 2.5e-5, 2.5e-5, 20, 2.5e-5, 2.5e-5, 20, 2.5e-5, 2.5e-5,20, 2.5e-5, 2.5e-5])

"""
