import pybullet as p
import pybullet_data
import time

physicsClient = p.connect(p.GUI)
p.setAdditionalSearchPath(pybullet_data.getDataPath())
p.setGravity(0,0,-9.8)
p.setRealTimeSimulation(1)

planeId = p.loadURDF("plane.urdf")

euler_angles = [0,0,0]
startOrientation = p.getQuaternionFromEuler(euler_angles)
startPosition = [0,0,0.5]

robotId = p.loadURDF("oruga_v6/urdf/oruga.urdf", startPosition, startOrientation)

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


articulaciones = [0, 8, 4, 12, 20, 16]
#art_1 = [0, 4, 20]
articulaciones_2 = [8, 12, 16]

inicio = time.time()

while (time.time() - inicio) < 2:
    p.setJointMotorControlArray(robotId, articulaciones_2, p.VELOCITY_CONTROL, 
                          targetVelocities=[2,2,2])



while (1):
    p.setJointMotorControlArray(robotId, articulaciones, p.VELOCITY_CONTROL, 
                          targetVelocities=[6,6,6,6,6,6])
    

p.disconnect()

    

