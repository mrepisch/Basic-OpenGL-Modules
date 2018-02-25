"""
*??
* TODO: @dominik comment 
"""
bl_info = {
	"name": "BGL Text Format (.xml)",
	"description": "Eport the model in a .xml format it's a xml based model format for the BGL libery.",
	"author": "Dominik Meier",
	"version": (1,6),
	"blender": (2, 7, 7),
	"api":  36079,
	"location": "File > Export > BGL Text Format (.xml)",
	"warning": "The model must be in triangels face", # used for warning icon and text in addons panel
	"wiki_url": "",
	"tracker_url": "",
	"category": "Import-Export"}


"""
* imports 
"""
import bpy
from bpy_extras.io_utils import ExportHelper
from bpy.props import StringProperty, BoolProperty, EnumProperty
from xml.dom.minidom import * 
import os
	
"""
* Datacontainsers 
* TODO: @domenik comment
"""
export_v = []
export_i = []
export_n = []
export_uv = []
vertices_groups = {} 
uv_layers = {} 

"""
* Search in the vertex with the given texture cordinates in the export_v array.
* If the vertex with the given cordinats dosen't exists then a new one will be created
* otherwise it returns the index in the array.
"""
def find_texture( uv1, uv2, x, y, z, nx, ny, nz ):
	global export_v
	num = 0
	vert = [x, y, z, uv1, uv2, num, nx, ny, nz]
	ev = 1

	#search the vertrix in the exportrt vertrex list
	for v in export_v:
		if v[0] == x:
			if v[1] == y:
				if v[2] == z:
					if v[3] == uv1:
						if v[4] == uv2:
							#Vertrex gefunden
							ev = 0
							break
		num += 1

	if ev == 1:
		vert[5] = num
		export_v.append(vert)
	return num

"""
* Funtion to search the given vertexID for the uv cordinates ???
* TODO: @dominik check comment, add additional infos
"""
def find_uv(uv1, uv2, vertInternID):
	global export_uv
	num = 0
	vert = [uv1, uv2, vertInternID, num]
	ev = 1

	#search the vertrix in the exportrt vertrex list
	for v in export_uv:
		if v[0] == uv1:
			if v[1] == uv2:
				if v[2] == vertInternID:
					ev = 0
					break
		num += 1

	if ev == 1:
		vert[3] = num
		export_uv.append(vert)
	return num

"""
* Function to search in the vgroup if a vertex allready is added to the group list
* @author the0815pimp
* @param int the group_id to look up for
* @param int vertex_index, the vertex index to search in the vgroup
"""
def is_vertrics_group(group_id, vertrex_index):
	for vgroup in vertices_groups[group_id]:
		if vgroup[0] == vertrex_index:
			return 0
	return 1

"""
* No fucking clue wat this is :) 
* @author the0815pimp
* @param ???
* TODO @the0815pimp comment
"""
def getPoseBoneLocalMatrix(poseBone): 
	if poseBone.parent is None: 
		return poseBone.matrix 
	else: 
		return poseBone.parent.matrix.inverted() * poseBone.matrix

"""
* Function to collect the uv data ??
* @author the0815pimp
* @param type ? ob, ?
* TODO: @the0815pimp comment
"""
def featchUV(ob):
	cnt_faces   = 0
	vertIdx = 0
	uvName = ''
	del export_uv[:]
	mesh = ob.data
	
	for face in mesh.polygons:
		#Internal counter for vertrex in face
		cnt_vetrex = 0
		
		#Speicher fuer die indexes dieser reihe
		vertrex_uv = [0, 0]

		#Durchlaufe die Vertrex im Face
		for vert in face.vertices:
			
			#Appliing worldmatrix to the actual vertrex
			#vertPosition = ob.matrix_world * mesh.vertices[vert.numerator].co
			
			#Need Local position
			vertPosition = mesh.vertices[vert.numerator].co
			vp_x = vertPosition.x
			vp_y = vertPosition.y
			vp_z = vertPosition.z
			
			vertNormal = mesh.vertices[vert.numerator].normal
			vn_x = vertNormal.x
			vn_y = vertNormal.y
			vn_z = vertNormal.z
			
			#Besitz UV Koordinaten  
			if len(mesh.uv_layers) > 0:
				uvLayer = mesh.uv_layers[0]
				uvPos = uvLayer.data[vertIdx]
				uv = uvPos.uv
				vertrex_uv=uv[0], 1.0-uv[1]
				uvName = uvLayer.name

			internal_vertrexID = find_texture( vertrex_uv[0], vertrex_uv[1], vp_x, vp_y, vp_z, vn_x, vn_y, vn_z )
			internal_UV = find_uv(vertrex_uv[0], vertrex_uv[1],internal_vertrexID)
			#face_data[3] = face.material_index
			
			print("UV %i: %f, %f" % (internal_UV, vertrex_uv[0], vertrex_uv[1]) )
			print("V %i:" % (internal_vertrexID) )
			
			#Zaehlvariable erhoehen
			cnt_vetrex += 1
			vertIdx += 1
		#Move face forward
		cnt_faces +=1
		
	for uv_vert in export_uv:
		uv_layers[uvName].append(uv_vert)

"""
* Function to collect data ??
* @author the0815pimp
* @param type ? obj ?
* TODO: @the0815pimp comment
"""
def featchData(ob):
	global export_v
	global export_i
	global export_n
	global export_uv
 
	#unset globals
	del export_v[:]
	del export_i[:]
	del export_n[:]
	del export_uv[:]
	
	cnt_faces   = 0
	vertIdx = 0
	#mesh = ob.data
	#generate pose mesh for the actual frame
	mesh = ob.to_mesh(bpy.context.scene, True, 'PREVIEW')
	for face in mesh.polygons:
		#Internal counter for vertrex in face
		cnt_vetrex = 0
		
		#Speicher fuer die indexes dieser reihe
		face_data = [0, 0, 0, 0, 0]
		face_normal = [0, 0, 0]

		#Durchlaufe die Vertrex im Face
		for vert in face.vertices:
	
			#Appliing worldmatrix to the actual vertrex
			vertPosition = mesh.vertices[vert.numerator].co
			vp_x = vertPosition.x
			vp_y = vertPosition.y
			vp_z = vertPosition.z
			
			vertNormal = mesh.vertices[vert.numerator].normal
			vn_x = vertNormal.x
			vn_y = vertNormal.y
			vn_z = vertNormal.z

			uvCoord = 1.5, 1.5
			
			#vertrx goup find and assign to export
			for goup in mesh.vertices[vert.numerator].groups:
				if is_vertrics_group(goup.group, mesh.vertices[vert.numerator].index):
					vgroup = [mesh.vertices[vert.numerator].index, goup.weight]
					vertices_groups[goup.group].append(vgroup)

			#Besitz UV Koordinaten  
			if len(mesh.uv_layers) > 0:
				uvLayer = mesh.uv_layers[0]
				uvLayer = uvLayer.data[vertIdx]
				uv=uvLayer.uv
				uvCoord=uv[0], 1.0-uv[1]

						
			face_data[cnt_vetrex] = find_texture( uvCoord[0], uvCoord[1], vp_x, vp_y, vp_z, vn_x, vn_y, vn_z )
			#Zaehlvariable erhoehen
			cnt_vetrex += 1
			vertIdx += 1
		
		#Export material & smoothness
		face_data[3] = face.material_index
		face_data[4] = face.use_smooth
			
		#Export normals
		face_normal[0] = face.normal[0]
		face_normal[1] = face.normal[1]
		face_normal[2] = face.normal[2]
		
		#Index der indexliste hinzufuegen
		export_i.append(face_data)
		export_n.append(face_normal)
		cnt_faces +=1
	#Remove pose mesh
	bpy.data.meshes.remove(mesh)


"""
* This funtion writes the material data into the given xml node.
* @author sascha blank
* @param Document p_xmlDoc, the xml document object(minidom)
* @param Node p_rootNode, the rootNode to add the new created nodes to
* @param ? p_material, the material data
* @param int p_matSlot, the id for the material ?
"""
def writeMaterials(p_xmlDoc, p_rootNode, p_material, p_matSlot):
	materialNode = p_xmlDoc.createElement("p_material")
	materialNode.setAttribute("id",str( p_matSlot ))
	p_rootNode.appendChild(materialNode)
	
	diffuseNode = p_xmlDoc.createElement("diffuse");
	colorNode = p_xmlDoc.createElement("color")
	colorNode.setAttribute("r", str(p_material.diffuse_color[0]))
	colorNode.setAttribute("g", str(p_material.diffuse_color[1]))
	colorNode.setAttribute("b", str(p_material.diffuse_color[2]))
	diffuseNode.appendChild(colorNode)
	materialNode.appendChild(diffuseNode)			
	
	specualNode = p_xmlDoc.createElement("specular");
	colorNode = p_xmlDoc.createElement("color")
	colorNode.setAttribute("r", str(p_material.specular_color[0]))
	colorNode.setAttribute("g", str(p_material.specular_color[1]))
	colorNode.setAttribute("b", str(p_material.specular_color[2]))
	specualNode.appendChild(colorNode)
	materialNode.appendChild(specualNode)			
	
	if p_material.use_transparency:
		alphaNode = p_xmlDoc.createElement("alpha")
		alphaNode.setAttribute("type","z-transparent")
		materialNode.appendChild(alphaNode)
	texturesetNode = p_xmlDoc.createElement("textureset")
	for texture_slot in p_material.texture_slots:
		if texture_slot:
			if texture_slot.use:
				texture_subclass = texture_slot.texture.image.name
				texture_cords = texture_slot.texture_coords
				textureSlotNode = p_xmlDoc.createElement("texture_slot")
				texturesetNode.appendChild(textureSlotNode)
				imageTag = p_xmlDoc.createElement("image")
				imageTag.setAttribute("url",texture_subclass)
				textureSlotNode.appendChild(imageTag)
				cordinateNode = p_xmlDoc.createElement("cordinate");
				cordinateNode.setAttribute("type",texture_cords)
				textureSlotNode.appendChild(cordinateNode)
				if texture_cords == 'UV':
					uvmapName = p_xmlDoc.createElement("uv_map")
					uvmapName.setAttribute("name", "texture_slot.uv_layer")
					textureSlotNode.appendChild(uvmapName)
	materialNode.appendChild(texturesetNode)

"""
* Function to write all vertecis data into the given rootnode
* @author the0815pimp & sascha blank
* @param Document p_xmlDoc, the document object (minidom)
* @param Node p_rootNode, the node to add the data to.
"""
def writeVertrex(p_xmlDoc, p_rootNode):
	global export_v
	verticesNodes = p_xmlDoc.createElement("vertices")
	print(export_v)
	for v in export_v:
		vertexNode = p_xmlDoc.createElement("vertex")
		positionNode = p_xmlDoc.createElement("position")
		positionNode.setAttribute("x",str( v[0] ))
		positionNode.setAttribute("y", str(v[1]))
		positionNode.setAttribute("z", str(v[2]))
		vertexNode.appendChild(positionNode)

		textcordNode = p_xmlDoc.createElement("textcord")
		textcordNode.setAttribute("layer","null")
		textcordNode.setAttribute("u",str(v[3]))
		textcordNode.setAttribute("v",str(v[4]))
		vertexNode.appendChild(textcordNode)

		normalNode = p_xmlDoc.createElement("normal")
		normalNode.setAttribute("x",str( v[6]))
		normalNode.setAttribute("y", str(v[7]))
		normalNode.setAttribute("z", str(v[8]))
		vertexNode.appendChild(normalNode)
		verticesNodes.appendChild(vertexNode)
	p_rootNode.appendChild(verticesNodes)

"""
* Function to collect and write the animation data into the given root node
* @author the0815pimp & sascha blank
* @param Document p_xmlDocument, the xml document object(minidom)
* @param p_obj, the data to use
* @param ? p_mode ??? TODO: @the0815pimp wat is p_mode??
"""
def export_actions(p_xmlDocument, p_rootNode, p_ob, p_mode):
	#print throught actions and write the data stuff 
	actionListNode = p_xmlDocument.createElement( "actionlist")
	for action in bpy.data.actions: 
		actionNode = p_xmlDocument.createElement("action")
		actionNode.setAttribute("name",action.name)
		actionListNode.appendChild(actionNode)
		armature_ob = p_ob
		#Check if animation over bone and set the action object
		if ob.modifiers:
			for modifier in ob.modifiers:
				if modifier.type == 'ARMATURE':
					print ('Found armature to atached object')
					armature_ob = modifier.object

			armature_ob.animation_data.action = action 
			#Muss bei bone animationen ausgefürt werden
			bpy.context.scene.objects.active = armature_ob
			bpy.ops.object.mode_set(mode="POSE") 
			bpy.ops.pose.select_all(action="SELECT") 
			bpy.ops.pose.transforms_clear() 

		#Write frame number in the animation
		(start_frame, end_frame) = armature_ob.animation_data.action.frame_range
		
		framesNode = p_xmlDocument.createElement("frames")
		framesNode.setAttribute("number", end_frame)
		actionListNode.appendChild(framesNode)
		if mode == '1':
			#Export animation by Bones and keyframes
			
			# get all frame numbers in this action 
			frames = dict() 
			frame_num = 0
			for fcurve in action.fcurves: 
				for key in fcurve.keyframe_points: 
					frame = key.co.x 
					frames[frame] = 1 
					frame_num = frame

			#Export animation per Key Frame
			for f in sorted(frames):
				bpy.context.scene.frame_set(f) 
				frameNode = p_xmlDocument.createElement("frame")
#		 Get the Actual export data from blender for this frame
				featchData(p_ob)
				#Write vertrex data again   
				writeVertrex(p_xmlDocument,frame)
				#Exporting Pose Bone for Bone animation 
				framesNode.appendChild(frameNode)

		else:
			#Export animation per Frame
			bpy.context.scene.objects.active = ob
			for f in range(int(start_frame), int(end_frame) + 1):
				#Write the amount of frames in this action
				frameNode = p_xmlDocument.createElement("frame")
				frameNode.setAttribute("number",f)
				bpy.context.scene.frame_set(f) 
				bpy.context.scene.update()
				
				#Get the Actual export data frlom blender for this frame
				featchData(ob)
				#Write vertrex data again   
				writeVertrex(p_xmlDocument, frameNode)
				framesNode.appendChild(frameNode)
	#Select exportet mesh again
	bpy.context.scene.objects.active = p_ob


"""
* Function to write the vertex group data into the given root node 
* @author sascha blank
* @param Document p_xmlDocument, the xml document object(minidom)
* @param Node p_rootNode, the root node to add the data to.
* @param p_vertexGroup, vertex group data object
"""
def writeVertexGroup(p_xmlDocument, p_rootNode, p_vertrex_group):
	groupNode = p_xmlDocument.createElement("group")
	groupNode.setAttribute("id", str(p_vertrex_group.index) )
	groupnode.appendChild(p_xmlDocument.createTextNode(str(p_vertrex_group.name)))
	for vgroup in vertices_groups[p_vertrex_group.index]:
		vertexNode = xmlDocument("vertex")
		vertexNode.setAttribute("id",str(vgroup[0]))
		vertexNode.setAttribute("weight", str(vgroup[1]))
		groupNode.appendChild(vertexNode)
	p_rootNode.appendChild(groupNode)


"""
* Function to write the UV layer data into the given root node
* @author sascha blank
* @param Document p_xmlDocument, the xml document node
* @param Node p_rootNode, the root node to add the data to
* @param p_uv_layer, data object of the uvlayer
* @param p_listWithUVLayers, list with the uv layer data
"""
def writeUVLayer(p_xmlDocument, p_rootNode, p_uv_layer, p_listWithUVLayers ):
	layerNode = p_xmlDocument.createElement("layer")
	layerNode.appendChild( p_xmlDocument.createTextNode(p_uv_layer.name))
	for uvcoord in p_listWithUVLayers[p_uv_layer.name]:
		cordNode = p_xmlDocument.createElement("coord")
		cordNode.setAttribute("u", str(uvcoord[0]))
		cordNode.setAttribute("v", str(uvcoord[1]))
		layerNode.appendChild(cordNode)
	p_rootNode.appendChild(layerNode)

"""
* Function to write the face data into the given xml root node
* @author sascha blank
* @param Document p_xmlDocument, the xml document object(minidom)
* @param Node p_rootNode, the root node to add the data to
* @param indices, data object of the face
* @param int faceID, the face id 
* @param p_export_n, ?? TODO:@the0815pimp wat is p_export_n
"""
def writeFaces(p_xmlDocumant, p_rootNode, indices, faceID, p_export_n):
	faceNode = p_xmlDocumant.createElement("face")
	faceNode.setAttribute("id", str(faceID))
	faceNode.setAttribute("v1", str(indices[0]))
	faceNode.setAttribute("v2", str(indices[1]))
	faceNode.setAttribute("v3", str(indices[2]))
	faceNode.setAttribute("material", str(indices[3]))
	faceNode.setAttribute("smooth", str(indices[4]))
	
	normalNode = p_xmlDocumant.createElement("normal")
	normalNode.setAttribute("x",str(p_export_n[faceID][0]))
	normalNode.setAttribute("y",str(p_export_n[faceID][1]))
	normalNode.setAttribute("z",str(p_export_n[faceID][1]))
	faceNode.appendChild(normalNode)
	p_rootNode.appendChild(faceNode)


def exportMeshes(context, filepath, bAnimExport, AnimType):
	print("start exporting the meshes ... ")
	global export_v
	global export_i
	global export_n
	global export_uv

	#Get selectet object
	oldObj = bpy.context.selected_objects;
	#bpy.ops.object.duplicate()
	#newObj = bpy.context.selected_objects;
	print("Colleting data...")
	objN = 0;
	#create new xml document
	xmlDocument = Document()
	for obj in oldObj:
		bpy.ops.object.select_all(action='DESELECT')
		obj.select = True
		
		bpy.ops.object.duplicate()
		obj.select = False
		
		newObj = bpy.context.selected_objects[0];
		
		print ('obje %s : %s' % (obj.name, newObj.name) )
		
		#Activate the object & convertet to triangles
		bpy.context.scene.objects.active = newObj
		bpy.ops.object.editmode_toggle()
		bpy.ops.mesh.select_all(action='SELECT')
		bpy.ops.mesh.quads_convert_to_tris(quad_method='BEAUTY', ngon_method='BEAUTY')
		bpy.ops.object.editmode_toggle()
		
		#-------------------------------------------------------------
		#Doo export code
		#-------------------------------------------------------------
		#Get the selectet mesh file
		#sce = bpy.data.scenes.active
		#ob = bpy.data.scenes[0].objects.active
		ob = newObj
		mesh = newObj.data

		#vertrex group create dictionery with list
		for vertrex_group in ob.vertex_groups:
			print ('vertrex Group_%i: %s' % (vertrex_group.index, vertrex_group.name) )
			vertices_groups[vertrex_group.index] = list()
			
		for uv_layer in ob.data.uv_layers:
			print ('uv Layer: %s' % (uv_layer.name) )
			uv_layers[uv_layer.name] = list()
			featchUV(ob)

		vert_id = 0
		vert_face = 0
		search_ok = 0
		num_face =  0
		num_vertrex = 0
		cnt_faces   = 0
		vertIdx = 0
		
		featchData(ob)
		
		for v in export_v:
			num_vertrex +=  1
		
		for indes in export_i:
			num_face += 1


		#try:
		print("start writing mesh to the xml document")
		#meshnode this node acts as current rootnode
		meshNode = xmlDocument.createElement("mesh")
		meshNode.setAttribute("max_vertices", str(num_vertrex))
		meshNode.setAttribute("max_faces", str(num_vertrex))

		
		materialsNode = xmlDocument.createElement("materials")
		#write the materials
		mat_slot = 0
		for material in mesh.materials:
			writeMaterials(xmlDocument,materialsNode,material,mat_slot)
			mat_slot += 1
		meshNode.appendChild(materialsNode)	
		
		#write vertex group
		verticesGroupNode = xmlDocument.createElement("vertices_group")
		for vertrex_group in ob.vertex_groups:
			writeVertexGroup(xmlDocument,verticesGroupNode,vertrex_group)
		meshNode.appendChild(verticesGroupNode)
		
		#write UV layer
		uvLayerNode = xmlDocument.createElement("uv_layer")
		for uv_layer in ob.data.uv_layers:
			writeUVLayer(xmlDocument,uvLayerNode,uv_layer,uv_layers)
		meshNode.appendChild(uvLayerNode)	
		
		#writeVertex
		writeVertrex(xmlDocument,meshNode)
		
		#write faces
		facesIdCounter = 0
		facesNode = xmlDocument.createElement("faces")
		for indes in export_i:
			writeFaces(xmlDocument,facesNode,indes,facesIdCounter,export_n)
			facesIdCounter += 1
		meshNode.appendChild(facesNode)
		
		#write animations if there are some
		if bAnimExport:
			export_actions(xmlDocument,meshNode, ob, AnimType)	
		xmlDocument.appendChild(meshNode)
		#except:
	#		print("CRITICAL ERROR: Something went wrong during the writing of the xml. Contact the devs of this script :) ")
	
	#xml creation complete print the result into the terminal and write it to a file
		#try:
		outputString = xmlDocument.toprettyxml()
		#print(outputString) #prints the whole xml for debug purposes
		outputFile = open( filepath, 'w')
		outputFile.write(outputString)
		outputFile.close()
		#except:
			#print("CRITICAL ERROR: Somthing went wrong during the filewriting")
	print("Export complete !!! \o/ Party time GG ")
	return {'FINISHED'}


"""
* Class which acts as interface to blender.
* @author the0815pimp
* TODO: @the0815pimp more details ?
"""
class BlenderInterface(bpy.types.Operator, ExportHelper):
	'''This appiers in the tooltip of the operator and in the generated docs.'''
	bl_idname = "export.bgl"	# this is important since its how bpy.ops.export.some_data is constructed
	bl_label = "BGL XML mesh export (.xml)"

	# ExportHelper mixin class uses this
	filename_ext = ".xml"

	filter_glob = StringProperty(default="*.xml", options={'HIDDEN'})

	# List of operator properties, the attributes will be assigned
	# to the class instance from the operator settings before calling.
	expAnimation = BoolProperty(
		name="Export Animation", 
		description="Exporting Animation", 
		default=True)

	expAnimType = EnumProperty(
		items=( ('1', "Key Frame", "Export the animation by keyframes"),
			('2', "Vertrex / Frame", "Each action has a list of frames that hold the complet animation data."),),
			name="Type: ",
			description="Choose the type of animation to export.",
			default='2')
	

	@classmethod
	def poll(cls, context):
		return context.active_object != None

	def execute(self, context):
		return exportMeshes(context, self.filepath, self.expAnimation, self.expAnimType)


# Only needed if you want to add into a dynamic menu
def menu_func_export(self, context):
	self.layout.operator(BlenderInterface.bl_idname, text="BGL XML mesh (.xml)")


def register():
	bpy.utils.register_class(BlenderInterface)
	bpy.types.INFO_MT_file_export.append(menu_func_export)


def unregister():
	bpy.utils.unregister_class(BlenderInterface)
	bpy.types.INFO_MT_file_export.remove(menu_func_export)

# test call
if __name__ == "__main__":
	register()
	bpy.ops.export.bgl('INVOKE_DEFAULT')
	
