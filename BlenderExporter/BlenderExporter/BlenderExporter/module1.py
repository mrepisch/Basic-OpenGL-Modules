""""
		#convert filepath to use the name of the original object
		path = os.path.normcase(os.path.dirname(filepath) + '/'+ obj.name + '.xml')
		f = open(path, 'w')
		
		#Daten zusammenkramen
		f.write( '<mesh max_vertices=\"%i\" max_faces=\"%i\">\n' % ( num_vertrex, num_face) )
		
		#Write matirial
		mat_slot = 0
		f.write( '<matrials>\n')
		for material in mesh.materials:
			f.write( '\t<matrial id="%i"> %s\n' % ( mat_slot, material.name) )
			f.write( '\t\t<diffuse>\n')
			f.write( '\t\t\t<color r="%f" g="%f" b="%f" />\n' % (material.diffuse_color[0], material.diffuse_color[1], material.diffuse_color[2]) )
			f.write( '\t\t</diffuse>\n')
			f.write( '\t\t<specular>\n')
			f.write( '\t\t\t<color r="%f" g="%f" b="%f" />\n' % (material.specular_color[0], material.specular_color[1], material.specular_color[2]) )
			f.write( '\t\t</specular>\n')
			
			#matrial suport alpha
			if (material.use_transparency):
				f.write('\t\t<alpha type="z-transparent"> </alpha>\n');

			#if 1:
			#	texture_slot1 = material.texture_slots[0];
			#	texture_image = texture_slot1.texture.image.name
			#	f.write('\t\t\t\t\t<image url="%s" />\n' % (texture_image) )
			
			f.write( '\t\t<textureset>\n')
			#for i in range(len(material.texture_slots)): 
			for texture_slot in material.texture_slots:
				if texture_slot:
					if texture_slot.use:
						texture_subclass = texture_slot.texture.image.name
						texture_cords = texture_slot.texture_coords
					#	print("used slots: %s" % texture_subclass )
						f.write('\t\t\t\t<texture_slot>\n')
						f.write('\t\t\t\t\t<image url="%s" />\n' % (texture_subclass) )
						f.write('\t\t\t\t\t<cordinate type="%s" />\n' % (texture_cords) )
						#If is UV Texture add aditional data
						if texture_cords == 'UV':
							 f.write('\t\t\t\t\t<uv_map name="%s" />\n' % (texture_slot.uv_layer) )
						f.write('\t\t\t\t</texture_slot>\n')
				#i += 1
			f.write( '\t\t</textureset>\n')

			f.write( '\t</matrial>\n' )
			mat_slot += 1
		f.write( '</matrials>\n')
		
		#Export UVLayers


		#Write Groups
		f.write( '<vertices_group>\n')
		for vertrex_group in ob.vertex_groups:
			f.write( '\t<group id=\"%i\"> %s\n' % (vertrex_group.index, vertrex_group.name) )
			for vgroup in vertices_groups[vertrex_group.index]:
				f.write( '\t<vertex id=\"%i\" weight=\"%f\" />\n' % ( vgroup[0], vgroup[1] ) )  
			f.write( '\t</group>\n')
		f.write( '</vertices_group>\n')
		
		#Write UV
		f.write( '<uv_layer>\n')
		for uv_layer in ob.data.uv_layers:
			f.write( '\t<layer> %s\n' % (uv_layer.name) )
			for uvcoord in uv_layers[uv_layer.name]:
				f.write( '\t<coord u=\"%f\" v=\"%f\" />\n' % ( uvcoord[0], uvcoord[1] ) )  
			f.write( '\t</layer>\n')
		f.write( '</uv_layer>\n')

		writeVertrex(f)
		
		f.write( '<faces>\n')
		num_face = 0
		for indes in export_i:
			f.write( ' \t<face id=\"%i\" v1=\"%i\" v2=\"%i\" v3=\"%i\" matrial=\"%i\" smooth=\"%s\" >\n' % ( num_face, indes[0], indes[1], indes[2], indes[3], indes[4] ) )
			f.write( ' \t<normal x=\"%f\" y=\"%f\" z=\"%f\" />\n' % ( export_n[num_face][0], export_n[num_face][1], export_n[num_face][2] ) )
			f.write( '\t</face>\n')
			num_face += 1
		f.write( '</faces>\n')
		
		if bAnimExport:
			export_actions(f, ob, AnimType)

		f.write('</mesh>');
		f.close()
		
		print(bAnimExport)
		print(AnimType)

		
		
		#del vertices_groups[:]
		objN += 1
		bpy.ops.object.delete()
		#-----------------------------------------------------
		#	OLD EXPORT LOOP
		#-----------------------------------------------------

	
	#Select old object
	for obj in oldObj:
		bpy.context.scene.objects.active = obj
		obj.select = 1
	""""