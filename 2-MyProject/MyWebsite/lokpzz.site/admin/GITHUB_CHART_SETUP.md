# 📊 GitHub 图表配置指南

## 🎯 为什么 GitHub 图表没有显示？

因为 GitHub 图表默认是**禁用状态**，需要在后台手动启用！

---

## ✅ 启用步骤

### 1. 打开后台管理
```
访问：admin/dashboard.html
```

### 2. 进入 GitHub 图表设置
- 点击左侧菜单 **"📊 GitHub 图表"**

### 3. 配置 GitHub 图表
1. ✅ 勾选 **"启用 GitHub 图表"**
2. 输入 **GitHub 用户名**（例如：`lokpzz`）
3. （可选）输入自定义图表链接
4. 点击 **"💾 保存设置"**

### 4. 刷新前台
```
按 F5 刷新首页
```

---

## 📊 图表说明

### 默认图表服务
使用 `https://ghchart.rshah.org/` 提供的免费 GitHub 贡献图表

### 图表 URL 格式
```
https://ghchart.rshah.org/000000/你的 GitHub 用户名
```

### 自定义图表（可选）
如果不想使用默认服务，可以输入自定义链接，例如：
- GitHub Profile 页面：`https://github.com/lokpzz`
- 其他图表服务链接

---

## 🎨 显示位置

启用后，GitHub 图表将显示在：
- **skills 标题下方**
- **图三图片下方**
- **白色半透明背景容器**

---

## 🔧 技术细节

### 数据结构
```javascript
github: {
    enabled: false,        // 默认禁用，需手动启用
    username: 'lokpzz',    // GitHub 用户名
    customUrl: ''          // 自定义链接（可选）
}
```

### 图表容器
```html
<div id="githubChart" style="...">
    <img src="https://ghchart.rshah.org/000000/lokpzz" alt="GitHub Contributions">
</div>
```

---

## 📞 常见问题

### Q: 图表不显示？
**A:** 检查以下几点：
1. 是否勾选"启用 GitHub 图表"
2. GitHub 用户名是否正确
3. 是否刷新了前台页面
4. 检查浏览器控制台是否有错误

### Q: 图表显示异常？
**A:** 可能是：
1. GitHub 用户名错误
2. ghchart 服务暂时不可用
3. 网络连接问题

### Q: 如何更换图表样式？
**A:** 可以：
1. 使用自定义 URL 参数，如：
   - `https://ghchart.rshah.org/202020/lokpzz` (深色主题)
   - `https://ghchart.rshah.org/FF0000/lokpzz` (红色主题)
2. 使用其他 GitHub 图表服务

---

## 🎉 示例配置

### 示例 1：基本配置
- 启用：✅
- 用户名：`lokpzz`
- 自定义 URL：（留空）
- 结果：显示默认深色图表

### 示例 2：自定义颜色
- 启用：✅
- 用户名：`lokpzz`
- 自定义 URL：`https://ghchart.rshah.org/667eea/lokpzz`
- 结果：显示紫色主题图表

### 示例 3：使用 GitHub 链接
- 启用：✅
- 用户名：`lokpzz`
- 自定义 URL：`https://github.com/lokpzz`
- 结果：显示 GitHub 个人主页（不是图表）

---

## 💡 提示

1. **首次配置**：建议先使用默认服务测试
2. **图表颜色**：可以自定义 6 位颜色代码
3. **性能优化**：图表是图片，加载速度快
4. **响应式**：图表自动适应屏幕宽度

---

**🎉 配置完成！享受你的 GitHub 贡献图表吧！**
