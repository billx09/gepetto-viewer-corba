from gepetto.corbaserver import Client

cl = Client()

withWindow = True

sN = ""
if withWindow:
    wid = cl.gui.createWindow("test")
    cl.gui.createScene("scene")
    cl.gui.addSceneToWindow("scene", wid)
    sN = "scene/"

for _ in xrange(100):
    #cl.gui.addURDF(sN + "kitchen", "package://iai_maps/urdf/kitchen_area.urdf","")
    cl.gui.addURDF(sN + "kitchen", "package://hrp2_14_description/urdf/hrp2_14.urdf","")
    #cl.gui.addSceneToWindow(sN + "kitchen", wid)
    cl.gui.deleteNode(sN + "kitchen", True)
