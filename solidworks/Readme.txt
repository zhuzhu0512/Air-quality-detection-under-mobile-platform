命名标准：
	1.部件编号_部件名称(_规格).后缀名
	2.尽量使用英文名
部件编号：
	1.标准件尽量使用toolbox自带零件，如果新建，以标准号开头
	如：GB818__Screw_m4X25.SLDPRT
	2.专用部件以“MACMxxxxxx”开头
	如：MACM010101_UniversalWheel_1.5inch.SLDPRT
	MACM：Moving Air Condition Monitor
	1-2位：大组件	3-4位：小组件	5：零件级组件 	6：零件
	00：总装		00：直属零件		
	01：底盘		00：直属零件
			01：驱动组件
			02：电源组件	
	02：中层设备	00：直属零件
			
	03：外壳		00：直属零件
		
