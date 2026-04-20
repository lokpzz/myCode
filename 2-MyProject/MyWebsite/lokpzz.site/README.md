# ZYYO 主页

一个简洁的个人主页，支持完整的后台管理系统。

**演示站**: [https://zyyo.cc](https://zyyo.cc)  
**后台**: [https://zyyo.cc/admin](https://zyyo.cc/admin)

---

## ✨ 功能特性

### 前台
- 个人信息展示（头像、职业、描述）
- 项目作品展示
- 技能墙
- GitHub 贡献图表
- 社交链接
- 时间线
- 白天/黑夜模式切换
- 响应式设计

### 后台管理
- 📊 项目管理
- 🏷️ 标签管理
- ⏰ 时间线管理
- ℹ️ 个人信息管理（头像、背景、职业）
- ⚡ 技能墙管理
- 📊 GitHub 图表集成
- 🔗 社交链接管理
- ⚙️ 系统设置

---

## 🚀 快速开始

### 访问后台
```
直接访问：http://your-domain.com/admin/
```

### 本地测试
```bash
# 使用 Python
python -m http.server 8000

# 访问 http://localhost:8000/admin/
```

---

## 📁 文件结构

```
.
├── admin/              # 后台管理系统
│   ├── css/           # 样式文件
│   ├── js/            # 脚本文件
│   └── dashboard.html # 管理后台页面
├── static/            # 静态资源
│   ├── css/          # 样式文件
│   ├── img/          # 图片资源
│   ├── js/           # 脚本文件
│   └── svg/          # SVG 图标
├── index.html         # 前台首页
├── Caddyfile          # Caddy 配置
├── Dockerfile         # Docker 配置
└── docker-compose.yaml # Docker Compose 配置
```

---

## 💡 使用说明

### 后台管理
1. 访问 `admin/dashboard.html`
2. 无需登录，直接进入后台
3. 可视化管理所有内容
4. 数据保存在 localStorage

### 数据同步
- 后台修改后，刷新前台即可看到最新内容
- 数据自动保存，无需手动导出

---

## 🛠️ 部署

### Docker 部署
```bash
docker compose up -d
```

### Caddy 部署
1. 修改 `Caddyfile` 中的域名
2. 启动 Caddy 服务
3. 自动配置 SSL 证书

---

## 📝 技术栈

- HTML5
- CSS3
- JavaScript (ES6+)
- LocalStorage API
- Caddy (部署)

---

## 🎨 主题

- 白天/黑夜模式
- 5 套白天主题
- 背景模糊效果
- 卡片模糊效果

---

## 📞 联系

- **QQ**: 3509679579
- **QQ 交流群**: 560938976
- **邮箱**: i@zyyo.net

---

## 📄 许可证

MIT License

---

## 🙏 鸣谢

- [iconfont](https://www.iconfont.cn) - 图标库
- [skill-icons](https://github.com/tandpfun/skill-icons) - 技能图标
- [ghchart](https://github.com/rshah123/ghchart) - GitHub 图表

---

## 📈 Star History

[![Star History Chart](https://api.star-history.com/svg?repos=ZYYO666/homepage&type=Date)](https://star-history.com/#ZYYO666/homepage&Date)


