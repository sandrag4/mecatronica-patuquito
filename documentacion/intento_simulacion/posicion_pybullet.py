import pybullet as p
import pybullet_data
import time
import math

physicsClient = p.connect(p.GUI)
p.setAdditionalSearchPath(pybullet_data.getDataPath())
p.setGravity(0,0,-9.8)
#p.setRealTimeSimulation(1)

planeId = p.loadURDF("plane.urdf")

euler_angles = [0,0,0]
startOrientation = p.getQuaternionFromEuler(euler_angles)
startPosition = [0,0,0.5]

robotId = p.loadURDF("oruga_v7/urdf/oruga.urdf", startPosition, startOrientation)

print("joints: ")
for i in range(p.getNumJoints(robotId)):
    joint_info = p.getJointInfo(robotId, i)
    print("Joint", i, ":",  joint_info[1])

# Joint 0 : derecha_delante_joint
# Joint 8 : derecha_medio_joint
# Joint 4 : derecha_detras_joint

# Joint 12 : izquierda_delante_joint
# Joint 20 : izquierda_medio_joint
# Joint 16 : izquierda_detras_joint

"""-----------------------------------------------"""

# Joint 0 : derecha_delante_joint
# Joint 1 : Cube_derecha_delante_joint

# Joint 8 : derecha_medio_joint
# Joint 9 : Cube_derecha_medio_joint

# Joint 4 : derecha_detras_joint
# Joint 5 : Cube_derecha_detras_joint



# Joint 12 : izquierda_delante_joint
# Joint 13 : Cube_izquierda_delante_joint

# Joint 20 : izquierda_medio_joint
# Joint 21 : Cube_izquierda_medio_joint

# Joint 16 : izquierda_detras_joint
# Joint 17 : Cube_izquierda_detras_joint



#articulaciones = [0, 8, 4, 12, 20, 16]
#art_1 = [0, 4, 20]
#articulaciones_2 = [8, 12, 16]

articulaciones = [0, 4, 20, 8, 12, 16]
cube_articulaciones = [1, 5, 21, 9, 13, 17]

inicio = time.time()


# --- Desactivar motores por defecto ---
#for j in range(p.getNumJoints(robotId)):
#    p.setJointMotorControl2(robotId, j, p.VELOCITY_CONTROL, force=0)

# --- Definición de articulaciones ---
grupoA = [0, 4, 20]
grupoB = [8, 12, 16]
grupoCubeA = [1, 5, 21]
grupoCubeB = [9, 13, 17]

Kp = 3.0
max_force = 100
velocidad = 0.01  # rad/s
t = 0

while True:
    angle = velocidad * t  # rotación continua

    target_A = angle
    target_B = angle + math.pi  # desfase π

    vel_A, vel_B, vel_cube_A, vel_cube_B = [], [], [], []

    # Grupo A
    for j in grupoA:
        pos = p.getJointState(robotId, j)[0]
        error = (target_A - pos + math.pi) % (2*math.pi) - math.pi
        vel_A.append(Kp * error)
        vel_cube_A.append(Kp * error)

    # Grupo B
    for j in grupoB:
        pos = p.getJointState(robotId, j)[0]
        error = (target_B - pos + math.pi) % (2*math.pi) - math.pi
        vel_B.append(Kp * error)
        vel_cube_B.append(Kp * error)

    joint_indices = grupoA + grupoB + grupoCubeA + grupoCubeB
    joint_vels = vel_A + vel_B + vel_cube_A + vel_cube_B

    p.setJointMotorControlArray(robotId, joint_indices, p.VELOCITY_CONTROL,
                                targetVelocities=joint_vels,
                                forces=[max_force]*len(joint_indices))

  

    p.stepSimulation()
    time.sleep(1/240)
    t += 1


p.disconnect()

    

