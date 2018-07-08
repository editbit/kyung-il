#include "stdafx.h"
#include "GamePlayScene.h"

HRESULT GamePlayScene::init()
{
	_bgImage = IMAGEMANAGER->addImage("playBackground", "resource\\titanSoulsMap_3160x8210.bmp", 3160, 8210);
	player = new Player;
	player->init();

	curMap = 0;

	initStage();

	return S_OK;
}

void GamePlayScene::release()
{
	player->release();
	for (int i = 0; i < MAX_MAP; ++i)
	{
		map[i].wall.clear();
	}
}

void GamePlayScene::update()
{
	player->update();
	setCamera(player->getX(), player->getY());

	collide();
}

void GamePlayScene::render()
{
	
	_bgImage->render(getMemDC(), 0, 0, camera.left, camera.top, WINSIZEX, WINSIZEY);

	player->setCamera({ camera.left, camera.top });
	player->render();

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		rendWallRECT();
	}
}

void GamePlayScene::setCamera(int x, int y)
{
	if (x < WINSIZEX / 2)
		x = WINSIZEX / 2;
	if (x + WINSIZEX / 2 > _bgImage->getWidth())
		x = _bgImage->getWidth() - WINSIZEX / 2;

	if (y < WINSIZEY / 2)
		y = WINSIZEY / 2;
	if (y + WINSIZEY / 2 > _bgImage->getHeight())
		y = _bgImage->getHeight() - WINSIZEY / 2;

	camera = RectMakeCenter(x, y, WINSIZEX, WINSIZEY);

}


void GamePlayScene::rendWallRECT()
{
	for (int i = 0; i < map[curMap].wall.size(); ++i)
	{
		Rectangle(getMemDC(), map[curMap].wall[i].left - camera.left, map[curMap].wall[i].top - camera.top,
			map[curMap].wall[i].right - camera.left, map[curMap].wall[i].bottom - camera.top);
	}
}

void GamePlayScene::collide()
{
	RECT temp;
	for (int i = 0; i < map[curMap].wall.size(); ++i)
	{
		if (IntersectRect(&temp, &player->getCollisionBox(), &map[curMap].wall[i]))
		{
			player->collideWall(map[curMap].wall[i]);
		}
	}
}


void GamePlayScene::initStage()
{
	map[0].wall.push_back({ 1226, 7916, 1941, 7947 });
	map[0].wall.push_back({ 1225, 7241, 1271, 7932 });
	map[0].wall.push_back({ 1898, 7242, 1941, 7925 });
	map[0].wall.push_back({ 1226, 7242, 1512, 7336 });
	map[0].wall.push_back({ 1657, 7244, 1933, 7332 });
	map[0].wall.push_back({ 1464, 7005, 1511, 7299 });
	map[0].wall.push_back({ 1658, 7004, 1702, 7294 });
	map[0].wall.push_back({ 938, 7006, 1493, 7190 });
	map[0].wall.push_back({ 935, 5996, 981, 7043 });
	map[0].wall.push_back({ 933, 5755, 1269, 6043 });
	map[0].wall.push_back({ 1175, 5614, 1507, 5767 });
	map[0].wall.push_back({ 1420, 6270, 1451, 6466 });
	map[0].wall.push_back({ 1420, 6269, 1750, 6294 });
	map[0].wall.push_back({ 1719, 6273, 1751, 6460 });
	map[0].wall.push_back({ 1463, 6471, 1707, 6506 });
	map[0].wall.push_back({ 1693, 6446, 1741, 6497 });
	map[0].wall.push_back({ 1436, 6446, 1500, 6496 });
	map[0].wall.push_back({ 1660, 7006, 2230, 7190 });
	map[0].wall.push_back({ 2185, 5995, 2230, 7034 });
	map[0].wall.push_back({ 1903, 5758, 2228, 6041 });
	map[0].wall.push_back({ 1272, 6182, 1898, 6281 });
	map[0].wall.push_back({ 1312, 6145, 1853, 6190 });
	map[0].wall.push_back({ 1346, 6114, 1822, 6158 });
	map[0].wall.push_back({ 1385, 6076, 1784, 6119 });
	map[0].wall.push_back({ 1416, 6044, 1753, 6087 });
	map[0].wall.push_back({ 1259, 5964, 1308, 6009 });
	map[0].wall.push_back({ 1285, 5941, 1329, 5980 });
	map[0].wall.push_back({ 1307, 5915, 1357, 5958 });
	map[0].wall.push_back({ 1339, 5883, 1384, 5934 });
	map[0].wall.push_back({ 1370, 5852, 1518, 5897 });
	map[0].wall.push_back({ 1653, 5851, 1805, 5900 });
	map[0].wall.push_back({ 1771, 5872, 1811, 5922 });
	map[0].wall.push_back({ 1808, 5906, 1848, 5951 });
	map[0].wall.push_back({ 1836, 5941, 1872, 5982 });
	map[0].wall.push_back({ 1867, 5970, 1904, 6010 });
	map[0].wall.push_back({ 1890, 5998, 1922, 6033 });
	map[0].wall.push_back({ 1461, 4750, 1507, 5636 });
	map[0].wall.push_back({ 1481, 5758, 1518, 5877 });
	map[0].wall.push_back({ 1652, 5750, 1684, 5877 });
	map[0].wall.push_back({ 1656, 5328, 1701, 5771 });
	map[0].wall.push_back({ 1677, 5613, 1992, 5795 });
	map[0].wall.push_back({ 1656, 5326, 2420, 5420 });
	map[0].wall.push_back({ 2372, 4797, 2422, 5355 });
	map[0].wall.push_back({ 1493, 5041, 2231, 5228 });
	map[0].wall.push_back({ 1656, 4753, 2377, 4938 });
	map[0].wall.push_back({ 1365, 4602, 1411, 4785 });
	map[0].wall.push_back({ 1366, 4749, 1504, 4844 });
	map[0].wall.push_back({ 1749, 4603, 1794, 4784 });
	map[0].wall.push_back({ 1365, 4602, 1518, 4652 });
	map[0].wall.push_back({ 1655, 4605, 1790, 4651 });
	map[0].wall.push_back({ 1412, 3737, 1455, 4612 });
	map[0].wall.push_back({ 1447, 4508, 1517, 4625 });
	map[0].wall.push_back({ 1649, 4507, 1720, 4650 });
	map[0].wall.push_back({ 1702, 3738, 1748, 4636 });
	map[0].wall.push_back({ 1700, 3735, 1843, 3833 });
	map[0].wall.push_back({ 1315, 3740, 1442, 3830 });
	map[0].wall.push_back({ 1317, 3258, 1363, 3775 });
	map[0].wall.push_back({ 1318, 3257, 1459, 3348 });
	map[0].wall.push_back({ 1410, 2727, 1458, 3297 });
	map[0].wall.push_back({ 1701, 2726, 1748, 3288 });
	map[0].wall.push_back({ 1702, 3257, 1842, 3348 });
	map[0].wall.push_back({ 1799, 3259, 1842, 3779 });
	map[0].wall.push_back({ 1701, 2726, 2517, 2965 });
	map[0].wall.push_back({ 1929, 2691, 2001, 2756 });
	map[0].wall.push_back({ 1959, 2660, 2010, 2711 });
	map[0].wall.push_back({ 1984, 2627, 2037, 2677 });
	map[0].wall.push_back({ 2016, 2601, 2071, 2653 });
	map[0].wall.push_back({ 2033, 2582, 2743, 2627 });
	map[0].wall.push_back({ 1217, 2726, 1441, 2769 });
	map[0].wall.push_back({ 1209, 2705, 1250, 2749 });
	map[0].wall.push_back({ 1194, 2685, 1229, 2734 });
	map[0].wall.push_back({ 1163, 2667, 1207, 2711 });
	map[0].wall.push_back({ 1144, 2644, 1186, 2698 });
	map[0].wall.push_back({ 1119, 2619, 1156, 2656 });
	map[0].wall.push_back({ 431, 2581, 1123, 2627 });
	map[0].wall.push_back({ 401, 2103, 450, 2600 });
	map[0].wall.push_back({ 980, 2391, 1192, 2487 });
	map[0].wall.push_back({ 1149, 2478, 1186, 2509 });
	map[0].wall.push_back({ 1175, 2497, 1207, 2534 });
	map[0].wall.push_back({ 1192, 2523, 1225, 2554 });
	map[0].wall.push_back({ 1219, 2542, 1245, 2572 });
	map[0].wall.push_back({ 1232, 2559, 1257, 2589 });
	map[0].wall.push_back({ 1253, 2583, 1281, 2618 });
	map[0].wall.push_back({ 1265, 2588, 1507, 2629 });
	map[0].wall.push_back({ 1650, 2580, 1893, 2626 });
	map[0].wall.push_back({ 432, 2105, 738, 2197 });
	map[0].wall.push_back({ 883, 2105, 1028, 2198 });
	map[0].wall.push_back({ 979, 2161, 1026, 2244 });
	map[0].wall.push_back({ 1053, 2365, 1093, 2410 });
	map[0].wall.push_back({ 1081, 2336, 1122, 2383 });
	map[0].wall.push_back({ 1106, 2309, 1145, 2349 });
	map[0].wall.push_back({ 1131, 2286, 1169, 2324 });
	map[0].wall.push_back({ 1153, 2265, 1183, 2302 });
	map[0].wall.push_back({ 1171, 2245, 1201, 2277 });
	map[0].wall.push_back({ 1194, 2219, 1227, 2259 });
	map[0].wall.push_back({ 1222, 2198, 1259, 2233 });
	map[0].wall.push_back({ 1243, 2172, 1276, 2207 });
	map[0].wall.push_back({ 1264, 2152, 1892, 2198 });
	map[0].wall.push_back({ 1018, 2172, 1049, 2221 });
	map[0].wall.push_back({ 1042, 2159, 1073, 2196 });
	map[0].wall.push_back({ 1071, 2134, 1097, 2170 });
	map[0].wall.push_back({ 1084, 2108, 1125, 2147 });
	map[0].wall.push_back({ 1124, 2088, 1149, 2124 });
	map[0].wall.push_back({ 1148, 2069, 1169, 2103 });
	map[0].wall.push_back({ 1162, 2046, 1193, 2074 });
	map[0].wall.push_back({ 1181, 2025, 1219, 2052 });
	map[0].wall.push_back({ 1198, 1996, 1241, 2029 });
	map[0].wall.push_back({ 1216, 1968, 1282, 2005 });
	map[0].wall.push_back({ 1266, 1864, 1363, 2001 });
	map[0].wall.push_back({ 2611, 2100, 2752, 2195 });
	map[0].wall.push_back({ 2709, 2134, 2755, 2629 });
	map[0].wall.push_back({ 2420, 2145, 2625, 2195 });
	map[0].wall.push_back({ 2131, 2146, 2275, 2194 });
	map[0].wall.push_back({ 2126, 2171, 2179, 2243 });
	map[0].wall.push_back({ 2021, 2390, 2179, 2482 });
	map[0].wall.push_back({ 1870, 2549, 1915, 2606 });
	map[0].wall.push_back({ 1893, 2536, 1938, 2582 });
	map[0].wall.push_back({ 1919, 2514, 1963, 2557 });
	map[0].wall.push_back({ 1947, 2480, 1986, 2534 });
	map[0].wall.push_back({ 1969, 2465, 2009, 2505 });
	map[0].wall.push_back({ 1985, 2442, 2030, 2481 });
	map[0].wall.push_back({ 1874, 2173, 1919, 2216 });
	map[0].wall.push_back({ 1910, 2196, 1945, 2236 });
	map[0].wall.push_back({ 1933, 2215, 1961, 2251 });
	map[0].wall.push_back({ 1951, 2238, 1980, 2278 });
	map[0].wall.push_back({ 1964, 2254, 1997, 2288 });
	map[0].wall.push_back({ 1988, 2276, 2019, 2310 });
	map[0].wall.push_back({ 2006, 2297, 2037, 2325 });
	map[0].wall.push_back({ 2026, 2310, 2053, 2340 });
	map[0].wall.push_back({ 2046, 2329, 2075, 2360 });
	map[0].wall.push_back({ 2060, 2352, 2093, 2381 });
	map[0].wall.push_back({ 2080, 2369, 2112, 2397 });
	map[0].wall.push_back({ 1797, 1862, 1890, 2004 });
	map[0].wall.push_back({ 1884, 1960, 1921, 2002 });
	map[0].wall.push_back({ 1908, 1989, 1943, 2019 });
	map[0].wall.push_back({ 1932, 2010, 1966, 2041 });
	map[0].wall.push_back({ 1958, 2035, 1998, 2068 });
	map[0].wall.push_back({ 1985, 2054, 2024, 2091 });
	map[0].wall.push_back({ 2012, 2079, 2049, 2116 });
	map[0].wall.push_back({ 2036, 2102, 2072, 2142 });
	map[0].wall.push_back({ 2061, 2132, 2094, 2163 });
	map[0].wall.push_back({ 2088, 2152, 2118, 2185 });
	map[0].wall.push_back({ 2104, 2172, 2137, 2203 });
	map[0].wall.push_back({ 2115, 2189, 2152, 2222 });
	map[0].wall.push_back({ 1255, 1541, 1507, 1621 });
	map[0].wall.push_back({ 1652, 1541, 1892, 1619 });
	map[0].wall.push_back({ 884, 85, 927, 1244 });
	map[0].wall.push_back({ 916, 1210, 953, 1266 });
	map[0].wall.push_back({ 941, 1234, 977, 1293 });
	map[0].wall.push_back({ 2226, 85, 2275, 1235 });
	map[0].wall.push_back({ 2195, 1217, 2242, 1271 });
	map[0].wall.push_back({ 2176, 1239, 2205, 1308 });
	map[0].wall.push_back({ 962, 1277, 996, 1318 });
	map[0].wall.push_back({ 987, 1300, 1026, 1343 });
	map[0].wall.push_back({ 1016, 1325, 1046, 1368 });
	map[0].wall.push_back({ 1035, 1352, 1072, 1388 });
	map[0].wall.push_back({ 1059, 1379, 1094, 1419 });
	map[0].wall.push_back({ 1084, 1402, 1115, 1440 });
	map[0].wall.push_back({ 1105, 1420, 1140, 1464 });
	map[0].wall.push_back({ 1126, 1441, 1158, 1485 });
	map[0].wall.push_back({ 1145, 1462, 1172, 1500 });
	map[0].wall.push_back({ 1163, 1479, 1192, 1519 });
	map[0].wall.push_back({ 1181, 1503, 1207, 1533 });
	map[0].wall.push_back({ 1197, 1517, 1226, 1552 });
	map[0].wall.push_back({ 1217, 1532, 1249, 1579 });
	map[0].wall.push_back({ 1233, 1558, 1266, 1595 });
	map[0].wall.push_back({ 1880, 1557, 1916, 1597 });
	map[0].wall.push_back({ 1895, 1536, 1935, 1568 });
	map[0].wall.push_back({ 1924, 1506, 1962, 1552 });
	map[0].wall.push_back({ 1949, 1487, 1988, 1523 });
	map[0].wall.push_back({ 1975, 1458, 2013, 1499 });
	map[0].wall.push_back({ 2006, 1440, 2034, 1478 });
	map[0].wall.push_back({ 2023, 1415, 2055, 1455 });
	map[0].wall.push_back({ 2038, 1392, 2081, 1428 });
	map[0].wall.push_back({ 2069, 1375, 2103, 1405 });
	map[0].wall.push_back({ 2093, 1359, 2124, 1392 });
	map[0].wall.push_back({ 2111, 1345, 2145, 1371 });
	map[0].wall.push_back({ 2132, 1322, 2167, 1357 });
	map[0].wall.push_back({ 2146, 1296, 2181, 1331 });
	map[0].wall.push_back({ 884, 84, 2259, 510 });

}
