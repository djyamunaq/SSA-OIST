import numpy as np
import matplotlib.pyplot as plt

def gillespie(c1, c2, A, B, C):
    '''
    1. Initialize the number of starting molecules xi for each species in the reaction network
    '''
    xa = [A]
    xb = [B]
    xc = [C]

    ts = [0]

    a0 = np.inf

    while True:
        '''
        2. Compute total reaction probability, a0=sum(ai) => ai=hi*xi => higher probability means time to next raction is smaller
        '''
        a1 = c1*xa[-1]
        a2 = c2*xb[-1]
        a0 = a1 + a2

        if a0 <= 0:
            break

        '''
        3. Select two random numbers, p1 and p2, from a uniform distribution on the interval (0, 1)
        '''
        r1 = np.random.uniform(0, 1)
        r2 = np.random.uniform(0, 1)

        '''
        4. Compute the time to next reaction tau=-ln(r1)/a0
        '''
        tau = -np.log(r1)/a0

        '''
        5. Select the reaction that takes place at this time => partition interval (0,1) by relative sizes of individual reaction provbabilities, then select the reaction that occurs using randomly generated number r2
        '''

        if r2*a0 < a1:
            # Reaction 1 occurs
            xa.append(xa[-1] - 1)
            xb.append(xb[-1] + 1)
            xc.append(xc[-1])
        else:
            # Reaction 2 occurs
            xa.append(xa[-1])
            xb.append(xb[-1] - 1)
            xc.append(xc[-1] + 1)

        '''
        6. Update reaction time t=t+tau => adjust number of molecules xi for each species
        '''
        ts.append(ts[-1] + tau)

        '''
        7. Return to step 2 and continue until total reaction probability is zero
        '''

    return xa, xb, xc, ts

def main():
    # Gillespie
    c1 = 0.5
    c2 = 0.1
    A = 1000
    B = 0
    C = 0
    xa, xb, xc, ts = gillespie(c1, c2, A, B, C)

    # plot xa, xb, xc vs time
    plt.plot(ts, xa, label='A')
    plt.plot(ts, xb, label='B')
    plt.plot(ts, xc, label='C')
    plt.xlabel('Time')
    plt.ylabel('Molecule Count')
    plt.legend()
    plt.show()

if __name__ == "__main__":
    main()